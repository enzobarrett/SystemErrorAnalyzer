#ifndef SYSTEMERROR_ANALYZER_RESULTS
#define SYSTEMERROR_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class SystemErrorAnalyzer;
class SystemErrorAnalyzerSettings;

class SystemErrorAnalyzerResults : public AnalyzerResults
{
public:
	SystemErrorAnalyzerResults( SystemErrorAnalyzer* analyzer, SystemErrorAnalyzerSettings* settings );
	virtual ~SystemErrorAnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	SystemErrorAnalyzerSettings* m_Settings;
	SystemErrorAnalyzer* m_Analyzer;
};

#endif //SYSTEMERROR_ANALYZER_RESULTS
