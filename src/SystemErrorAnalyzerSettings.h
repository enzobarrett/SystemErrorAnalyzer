#ifndef SYSTEMERROR_ANALYZER_SETTINGS
#define SYSTEMERROR_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class SystemErrorAnalyzerSettings : public AnalyzerSettings
{
public:
	SystemErrorAnalyzerSettings();
	virtual ~SystemErrorAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	U32 mBitRate;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
};

#endif //SYSTEMERROR_ANALYZER_SETTINGS
