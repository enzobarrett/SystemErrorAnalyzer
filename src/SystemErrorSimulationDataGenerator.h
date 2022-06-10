#ifndef SYSTEMERROR_SIMULATION_DATA_GENERATOR
#define SYSTEMERROR_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <AnalyzerHelpers.h>
#include <string>

class SystemErrorAnalyzerSettings;

class SystemErrorSimulationDataGenerator
{
public:
	SystemErrorSimulationDataGenerator();
	~SystemErrorSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, SystemErrorAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	SystemErrorAnalyzerSettings* m_Settings;
	U32 m_SimulationSampleRateHz;

protected:
    // create the data for one error display
	void CreatePeriod();

    // display a digit at hz
    void PulseDigit(int digit, int freq);

	SimulationChannelDescriptor m_SerialSimulationData;
	ClockGenerator m_Clock;

    int m_ErrorCode;
};
#endif //SYSTEMERROR_SIMULATION_DATA_GENERATOR