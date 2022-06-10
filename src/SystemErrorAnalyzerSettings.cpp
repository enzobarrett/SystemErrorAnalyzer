#include "SystemErrorAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


SystemErrorAnalyzerSettings::SystemErrorAnalyzerSettings()
:   m_InputChannel(UNDEFINED_CHANNEL),
    m_10sFreq(5), /* hz */
    m_Padding1(300), /* ms */
    m_1sFreq(10), /* hz */
    m_Padding2(600) /* ms */
{
	m_InputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	m_InputChannelInterface->SetTitleAndTooltip("Input Channel", "Standard System Error Analyzer" );
	m_InputChannelInterface->SetChannel( m_InputChannel );

	m_10sFreqInterface.reset( new AnalyzerSettingInterfaceInteger() );
	m_10sFreqInterface->SetTitleAndTooltip( "10s Frequency (hz)",  "Specify the frequency in hz." );
	m_10sFreqInterface->SetInteger( m_10sFreq );

	m_1sFreqInterface.reset( new AnalyzerSettingInterfaceInteger() );
	m_1sFreqInterface->SetTitleAndTooltip( "1s Frequency (hz)",  "Specify the frequency in hz." );
	m_1sFreqInterface->SetInteger( m_1sFreq );

	m_Padding1Interface.reset( new AnalyzerSettingInterfaceInteger() );
	m_Padding1Interface->SetTitleAndTooltip( "Padding Between 10s and 1s Digit (ms)",  "Specify the padding in ms." );
	m_Padding1Interface->SetInteger( m_Padding1 );

	m_Padding2Interface.reset( new AnalyzerSettingInterfaceInteger() );
	m_Padding2Interface->SetTitleAndTooltip( "Padding Between 1s and 10s Digit (ms)",  "Specify the padding in ms." );
	m_Padding2Interface->SetInteger( m_Padding2 );

	AddInterface( m_InputChannelInterface.get() );
	AddInterface( m_10sFreqInterface.get() );
	AddInterface( m_Padding1Interface.get() );
	AddInterface( m_1sFreqInterface.get() );
	AddInterface( m_Padding2Interface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( m_InputChannel, "Serial", false );
}

SystemErrorAnalyzerSettings::~SystemErrorAnalyzerSettings()
{
}

bool SystemErrorAnalyzerSettings::SetSettingsFromInterfaces()
{
	m_InputChannel = m_InputChannelInterface->GetChannel();
	m_10sFreq = m_10sFreqInterface->GetInteger();
	m_1sFreq = m_1sFreqInterface->GetInteger();
    m_Padding1 = m_Padding1Interface->GetInteger();
    m_Padding2 = m_Padding2Interface->GetInteger();

	ClearChannels();
	AddChannel( m_InputChannel, "System Error Analyzer", true );

	return true;
}

void SystemErrorAnalyzerSettings::UpdateInterfacesFromSettings()
{
	m_InputChannelInterface->SetChannel( m_InputChannel );
	m_10sFreqInterface->SetInteger( m_10sFreq );
	m_1sFreqInterface->SetInteger( m_1sFreq );
    m_Padding1Interface->SetInteger( m_Padding1 );
    m_Padding2Interface->SetInteger( m_Padding2 );
}

void SystemErrorAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> m_InputChannel;
	text_archive >> m_10sFreq;
	text_archive >> m_Padding1;
	text_archive >> m_1sFreq;
	text_archive >> m_Padding2;

	ClearChannels();
	AddChannel( m_InputChannel, "System Error Analyzer", true );

	UpdateInterfacesFromSettings();
}

const char* SystemErrorAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << m_InputChannel;
	text_archive << m_10sFreq;
	text_archive << m_Padding1;
	text_archive << m_1sFreq;
	text_archive << m_Padding2;

	return SetReturnString( text_archive.GetString() );
}
