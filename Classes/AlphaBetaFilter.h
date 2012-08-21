#ifndef ALPHA_BETA_FILTER_H_
#define ALPHA_BETA_FILTER_H_

#include <ostream>
#include <vector>

/** @brief Implements an Alpha-Beta filter
 *
 * An Alpha-Beta filter is a predictive filter used to filter out noise from a
 * noisy signal.  The filter is controlled by the two constants, Alpha and
 * Beta.
 *
 * See http://en.wikipedia.org/wiki/Alpha_beta_filter for more information.
 *
 * When logging is enabled the values are added to a container rather than being
 * written directly to the log.  This is to keep the filter running fast and
 * not be bogged down with slow IO code.
 *
 * @author Stephen Nutt
 * @version 1.0
 */
template <typename T>
class AlphaBetaFilter
{
public:
	//! Initializes everything in the filter to 0
	inline AlphaBetaFilter () :
		m_lastTime(), m_alpha(), m_beta(), m_value(), m_rateOfChange(),
		m_enableLogging (false), m_hasValue (false)
	{
	}

	//! Initializes the filter using the specified alpha and beta correction
	//! gains, everything else is initialized to 0
	inline AlphaBetaFilter (const T& alpha, const T& beta) :
		m_lastTime(), m_alpha(alpha), m_beta(beta), m_value(), m_rateOfChange(),
		m_enableLogging (false), m_hasValue (false)
	{
	}

	//! Clears the filter
	inline void Clear()
	{
		m_hasValue = false;
		m_value = T();
	}

	//! Sets the alpha beta correction gains
	inline void SetCorrectionGains (const T& alpha, const T& beta)
	{
		m_alpha = alpha;
		m_beta = beta;
	}

	//! Seeds the filter with an initial value and rate of change at a
	//! given time
	inline void SeedFilter (const T& value, const T& speed, const UINT32 now)
	{
		m_value = value;
		m_rateOfChange = speed;
		m_lastTime = now;
		m_hasValue = true;
	}

	//! Seeds the filter with an initial value at a given time but does not
	//! change the rate of change
	inline void SeedFilter (const T& value, const UINT32 now)
	{
		m_value = value;
		m_lastTime = now;
		m_hasValue = true;
	}

	//! Initializes the logging for the filter
	inline void EnableLogging()
	{
		m_enableLogging = true;
		m_history.reserve (1000);
	}

	//! Disabled the filter logging
	inline void DisableLogging()
	{
		m_enableLogging = false;
	}

	//! Returns true if filter logging is currently enabled
	inline bool IsLoggingEnabled() const
	{
		return m_enableLogging;
	}

	//! Writes the filter's history to the specified stream in a comma
	//! delimitered file format with a header line
	void WriteLog (std::ostream& os)
	{
		FilterHistory::WriteHeader (os);
		for (typename HistoryContainer::const_iterator i =
			m_history.begin(); i != m_history.end(); ++i)
		{
			os << *i;
		}
	}

	//! Updates the filter with using the new measured value and
	//! the time of the measurement, returning the smoothed value
	const T& Update (const T& measuredVal, const UINT32 measurementTime)
	{
		if (m_hasValue == false)
		{
			// First time through an unseeded filter without a previous value
			// we seed the filter.  This allows the filter to settle faster
			// if the target value is not 0 (the default value at construction
			// time).
			m_value = measuredVal;
			m_hasValue = true;
		}
		else
		{
			// If the filter has been previous seeded, or Update has been
			// previously called giving the filter a value, we push the
			// new value into the filter
			const double dTime = (measurementTime - m_lastTime) * 1e-6;
			const T predictedValue (m_value + m_rateOfChange * dTime);
			const T residual (measuredVal - predictedValue);
			m_value = predictedValue + m_alpha * residual;
			m_rateOfChange = static_cast<T> (m_rateOfChange + m_beta * residual / dTime);

			// If we are logging the values we add the new filter state to the
			// history container.
			if (m_enableLogging)
			{
				m_history.resize (m_history.size() + 1);
				FilterHistory& last = m_history.back();
				last.m_measuredVal = measuredVal;
				last.m_time = measurementTime;
				last.m_dTime = dTime;
				last.m_predictedValue = predictedValue;
				last.m_residual = residual;
				last.m_rateOfChange = m_rateOfChange;
				last.m_value = m_value;
			}
		}

		// Set the last measurement time
		m_lastTime = measurementTime;

		return m_value;
	}

	//! Returns the current filter value, this is the same as the last value
	//! returned by \c Update
	inline const T& GetValue() const
	{
		return m_value;
	}

	//! Returns the time of the last measurement passed to \Update
	inline UINT32 GetLastMeasurementTime() const
	{
		return m_lastTime;
	}

	//! Returns the rate of change in the filter
	inline const T& GetRateOfChange() const
	{
		return m_rateOfChange;
	}

private:
	/** @brief Contains the evaluation state of the filter for a single reading
	 *
	 * @version 1.0
	 */
	struct FilterHistory
	{
		T m_measuredVal;	//!< The measured value
		UINT32 m_time;		//!< The time of the reading
		double m_dTime;		//!< The time increment since the previous reading
		T m_predictedValue;	//!< The predicted value for this reading
		T m_residual;		//!< The residual between the predicted value and the measured value
		T m_rateOfChange;	//!< The rate of change of the filter at the reading
		T m_value;			//!< The new filter value

		//! Writes out the header for the log
		static inline void WriteHeader (std::ostream& os)
		{
			os << "Raw,Time,DeltaTime,Predicted,Residual,ROC,Value" << std::endl;
		}

		//! Writes out a single log line
		friend ostream& operator << (ostream& os, const FilterHistory& item)
		{
			// We use printf as it is faster and gives us better control of
			// the formatting
			char buffer[128];
			sprintf (buffer, "%.8f,%.8f,%.8f,%.8f,%.8f,%.8f,%.8f",
				static_cast<double> (item.m_measuredVal),
				static_cast<double> (item.m_time),
				static_cast<double> (item.m_dTime),
				static_cast<double> (item.m_predictedValue),
				static_cast<double> (item.m_residual),
				static_cast<double> (item.m_rateOfChange),
				static_cast<double> (item.m_value));

			return os << buffer << std::endl;
		}
	};

	//! The container type used for the filter logging
	typedef std::vector<FilterHistory> HistoryContainer;

	UINT32 m_lastTime;			//!< Time of last measurement
	T m_alpha;					//!< Alpha correction gain, used to smooth the value
	T m_beta;					//!< Beta correction gain, used to smooth the rate of change
	T m_value;					//!< The smoothed value
	T m_rateOfChange;			//!< The smoothed rate of change of the value
	bool m_enableLogging;		//!< When set to true, the filter state is stored in \c m_history
	bool m_hasValue;			//!< When set to false, the filter has yet to be seeded or fed a value
	HistoryContainer m_history;	//!< The filter history, only used for logging purposes
};

#endif
