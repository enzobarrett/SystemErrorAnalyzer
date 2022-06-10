#ifndef SYSTEMERROR_ANALYZER_H
#define SYSTEMERROR_ANALYZER_H

#include <Analyzer.h>
#include "SystemErrorAnalyzerResults.h"
#include "SystemErrorSimulationDataGenerator.h"

class SystemErrorAnalyzerSettings;
class ANALYZER_EXPORT SystemErrorAnalyzer : public Analyzer2
{
public:
	SystemErrorAnalyzer();
	virtual ~SystemErrorAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< SystemErrorAnalyzerSettings > mSettings;
	std::auto_ptr< SystemErrorAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	SystemErrorSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //SYSTEMERROR_ANALYZER_H
