// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "Common/ExpressionCommandSerializer.h"

using namespace CalculatorApp::ViewModel::Common;
using namespace Windows::Storage::Streams;

SerializeCommandVisitor::SerializeCommandVisitor(_In_ DataWriter ^ dataWriter)
    : m_dataWriter(dataWriter)
{
}

void SerializeCommandVisitor::Visit(_In_ COpndCommand& opndCmd)
{
    m_dataWriter->WriteBoolean(opndCmd.IsNegative());
    m_dataWriter->WriteBoolean(opndCmd.IsDecimalPresent());
    m_dataWriter->WriteBoolean(opndCmd.IsSciFmt());

    const auto& opndCmds = opndCmd.GetCommands();
    unsigned int opndCmdSize = static_cast<unsigned int>(opndCmds->size());
    m_dataWriter->WriteUInt32(opndCmdSize);
    for (int eachOpndcmd : *opndCmds)
    {
        m_dataWriter->WriteInt32(eachOpndcmd);
    }
}

void SerializeCommandVisitor::Visit(_In_ CUnaryCommand& unaryCmd)
{
    const auto& cmds = unaryCmd.GetCommands();
    unsigned int cmdSize = static_cast<unsigned int>(cmds->size());
    m_dataWriter->WriteUInt32(cmdSize);
    for (int eachOpndcmd : *cmds)
    {
        m_dataWriter->WriteInt32(eachOpndcmd);
    }
}

void SerializeCommandVisitor::Visit(_In_ CBinaryCommand& binaryCmd)
{
    int cmd = binaryCmd.GetCommand();
    m_dataWriter->WriteInt32(cmd);
}

void SerializeCommandVisitor::Visit(_In_ CParentheses& paraCmd)
{
    int parenthesisCmd = paraCmd.GetCommand();
    m_dataWriter->WriteInt32(parenthesisCmd);
}
