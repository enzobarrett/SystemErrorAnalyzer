#include "SystemErrorAnalyzer.h"
#include "SystemErrorAnalyzerSettings.h"
#include <AnalyzerChannelData.h>
#include <iostream>
#include <cmath>

SystemErrorAnalyzer::SystemErrorAnalyzer()
:	Analyzer2(),  
	m_Settings( new SystemErrorAnalyzerSettings() ),
	m_SimulationInitialized( false )
{
	SetAnalyzerSettings( m_Settings );
}

SystemErrorAnalyzer::~SystemErrorAnalyzer()
{
    delete m_Settings;
    delete m_Results;
	KillThread();
}

void SystemErrorAnalyzer::SetupResults()
{
	m_Results = new SystemErrorAnalyzerResults( this, m_Settings );
	SetAnalyzerResults( m_Results );
	m_Results->AddChannelBubblesWillAppearOn( m_Settings->m_InputChannel );
}

void SystemErrorAnalyzer::WorkerThread()
{
    m_SampleRateHz = GetSampleRate();

	m_Serial = GetAnalyzerChannelData( m_Settings->m_InputChannel );

    m_Serial->AdvanceToNextEdge();

    U64 last_edge = m_Serial->GetSampleNumber();
    U64 starting_sample = m_Serial->GetSampleNumber();

    // expected space between pulses
	U32 big_digit_space = (m_SampleRateHz / m_Settings->m_10sFreq) / 2;
    U32 small_digit_space = (m_SampleRateHz / m_Settings->m_1sFreq) / 2;
    U32 padding_1_space = static_cast<U32>(m_SampleRateHz * (m_Settings->m_Padding1 / 1000.0));
    U32 padding_2_space = static_cast<U32>(m_SampleRateHz * (m_Settings->m_Padding2 / 1000.0));

    int big_digit_count = 0;
    int small_digit_count = 0;

    // flag to reset starting sample
    bool reset_starting_sample = false;

    // how much error should we tolerate?
    int margin_of_error = 10'000'000;

	for( ; ; )
    {
        m_Serial->AdvanceToNextEdge();

        // how much time between last and current pulse?
        U64 diff = m_Serial->GetSampleNumber() - last_edge;
        last_edge = m_Serial->GetSampleNumber();

        if (std::abs(static_cast<int>(diff - big_digit_space)) < margin_of_error) {
            big_digit_count++;
        }
        if (std::abs(static_cast<int>(diff - small_digit_space)) < margin_of_error) {
            small_digit_count++;
        }
        if(std::abs(static_cast<int>(diff - padding_1_space)) < margin_of_error) {
            // our frame ends at the end off padding 2,
            // so we do all our work there
        }
        if(std::abs(static_cast<int>(diff - padding_2_space)) < margin_of_error) {
            // add a frame with the error code
            Frame frame;

            // convert # of pulses -> number
            int big_digit = static_cast<int>(std::ceil(big_digit_count / 2.0));
            int small_digit = static_cast<int>(std::ceil(small_digit_count / 2.0));

            // combine into two digit error code
            frame.mData1 = big_digit * 10 + small_digit;

            frame.mFlags = 0;


            // start at end of last padding 2
            frame.mStartingSampleInclusive = starting_sample;
            // end at beginning of this padding 2
            frame.mEndingSampleInclusive = last_edge - padding_2_space;

            // save our work
            m_Results->AddFrame(frame);
            m_Results->CommitResults();

            // reset count
            small_digit_count = 0;
            big_digit_count = 0;

            // set flag
            reset_starting_sample = true;
        }

        if (reset_starting_sample) {
            starting_sample = last_edge;
            reset_starting_sample = false;
        }

        ReportProgress( m_Serial->GetSampleNumber() );
    }
}

bool SystemErrorAnalyzer::NeedsRerun()
{
    return false;
}

U32 SystemErrorAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate,
                                                 SimulationChannelDescriptor** simulation_channels )
{
    if( m_SimulationInitialized == false )
    {
        m_SimulationDataGenerator.Initialize( GetSimulationSampleRate(), m_Settings );
        m_SimulationInitialized = true;
    }

    return m_SimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 SystemErrorAnalyzer::GetMinimumSampleRateHz()
{
    return 25000; // TODO: look into this
}

const char* SystemErrorAnalyzer::GetAnalyzerName() const
{
    return "System Error Analyzer";
}

const char* GetAnalyzerName()
{
    return "System Error Analyzer";
}

Analyzer* CreateAnalyzer()
{
    return new SystemErrorAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
    // TODO: implement fix for when we call delete here
}