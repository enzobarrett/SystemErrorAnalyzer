#include "SystemErrorSimulationDataGenerator.h"
#include "SystemErrorAnalyzerSettings.h"

#include <AnalyzerHelpers.h>

SystemErrorSimulationDataGenerator::SystemErrorSimulationDataGenerator() {}

SystemErrorSimulationDataGenerator::~SystemErrorSimulationDataGenerator() {}

void SystemErrorSimulationDataGenerator::Initialize( U32 simulation_sample_rate, SystemErrorAnalyzerSettings* settings )
{
	m_SimulationSampleRateHz = simulation_sample_rate;
	m_Settings = settings;
    m_ErrorCode = 42; // InvalidController
    m_Clock = ClockGenerator();

	m_SerialSimulationData.SetChannel( m_Settings->m_InputChannel );
	m_SerialSimulationData.SetSampleRate( simulation_sample_rate );
	m_SerialSimulationData.SetInitialBitState( BIT_HIGH );
}

U32 SystemErrorSimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, m_SimulationSampleRateHz );

	while( m_SerialSimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreatePeriod();
	}

	*simulation_channel = &m_SerialSimulationData;
	return 1;
}

void SystemErrorSimulationDataGenerator::CreatePeriod()
{
    // display 10s digit
    PulseDigit(m_ErrorCode / 10, m_Settings->m_10sFreq);

    // delay padding 1
    m_SerialSimulationData.Advance(m_Clock.AdvanceByTimeS((double) m_Settings->m_Padding1 / 1000 ));

    // display 1s digit
    PulseDigit(m_ErrorCode % 10, m_Settings->m_1sFreq);

    // delay padding 2
    m_SerialSimulationData.Advance(m_Clock.AdvanceByTimeS((double) m_Settings->m_Padding2 / 1000 ));
}

void SystemErrorSimulationDataGenerator::PulseDigit(int digit, int freq) {
    // init clock
    m_Clock.Init(freq, m_SimulationSampleRateHz);

    // loop through the digit and pulse
    for (int i = 0; i < digit; ++i) {
        // pull the line low
        m_SerialSimulationData.TransitionIfNeeded( BIT_LOW );

        // advance half period
        m_SerialSimulationData.Advance(m_Clock.AdvanceByHalfPeriod());

        // high again
        m_SerialSimulationData.TransitionIfNeeded( BIT_HIGH );

        // advance half period
        m_SerialSimulationData.Advance(m_Clock.AdvanceByHalfPeriod());
    }
}