#ifndef SYSTEMERROR_SIMULATION_DATA_GENERATOR
#define SYSTEMERROR_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
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
	SystemErrorAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //SYSTEMERROR_SIMULATION_DATA_GENERATOR