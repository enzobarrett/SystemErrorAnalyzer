#ifndef SYSTEMERROR_ANALYZER_H
#define SYSTEMERROR_ANALYZER_H

#include <Analyzer.h>
#include "SystemErrorAnalyzerResults.h"
#include "SystemErrorSimulationDataGenerator.h"

#pragma warning(disable: 4251)

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

private: //vars
	SystemErrorAnalyzerSettings* m_Settings;
	SystemErrorAnalyzerResults* m_Results;
	AnalyzerChannelData* m_Serial;

	SystemErrorSimulationDataGenerator m_SimulationDataGenerator;
	bool m_SimulationInitialized;

	//Serial analysis vars:
	U32 m_SampleRateHz;
	U32 m_StartOfStopBitOffset;
	U32 m_EndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //SYSTEMERROR_ANALYZER_H
