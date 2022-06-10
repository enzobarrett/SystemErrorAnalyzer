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


        Channel m_InputChannel;
        U32 m_10sFreq;
        U32 m_Padding1;
        U32 m_1sFreq;
        U32 m_Padding2;

    protected:
        std::auto_ptr<AnalyzerSettingInterfaceChannel> m_InputChannelInterface;
        std::auto_ptr<AnalyzerSettingInterfaceInteger> m_10sFreqInterface;
        std::auto_ptr<AnalyzerSettingInterfaceInteger> m_Padding1Interface;
        std::auto_ptr<AnalyzerSettingInterfaceInteger> m_1sFreqInterface;
        std::auto_ptr<AnalyzerSettingInterfaceInteger> m_Padding2Interface;
};

#endif // SYSTEMERROR_ANALYZER_SETTINGS
