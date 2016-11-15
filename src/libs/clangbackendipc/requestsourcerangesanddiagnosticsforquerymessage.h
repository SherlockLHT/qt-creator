/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "clangbackendipc_global.h"

#include "filecontainerv2.h"

namespace ClangBackEnd {

class CMBIPC_EXPORT RequestSourceRangesAndDiagnosticsForQueryMessage
{
public:
    RequestSourceRangesAndDiagnosticsForQueryMessage() = default;
    RequestSourceRangesAndDiagnosticsForQueryMessage(Utils::SmallString &&query,
                                                     std::vector<V2::FileContainer> &&fileContainers)
        : query_(std::move(query)),
          fileContainers_(std::move(fileContainers))
    {}

    const std::vector<V2::FileContainer> &fileContainers() const
    {
        return fileContainers_;
    }

    std::vector<V2::FileContainer> takeFileContainers()
    {
        return std::move(fileContainers_);
    }

    const Utils::SmallString &query() const
    {
        return query_;
    }

    Utils::SmallString takeQuery()
    {
        return std::move(query_);
    }

    friend QDataStream &operator<<(QDataStream &out, const RequestSourceRangesAndDiagnosticsForQueryMessage &message)
    {
        out << message.query_;
        out << message.fileContainers_;

        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, RequestSourceRangesAndDiagnosticsForQueryMessage &message)
    {
        in >> message.query_;
        in >> message.fileContainers_;

        return in;
    }

    friend bool operator==(const RequestSourceRangesAndDiagnosticsForQueryMessage &first,
                           const RequestSourceRangesAndDiagnosticsForQueryMessage &second)
    {
        return first.query_ == second.query_
               && first.fileContainers_ == second.fileContainers_;

    }

    RequestSourceRangesAndDiagnosticsForQueryMessage clone() const
    {
        return RequestSourceRangesAndDiagnosticsForQueryMessage(query_.clone(),
                                                                Utils::clone(fileContainers_));
    }

private:
    Utils::SmallString query_;
    std::vector<V2::FileContainer> fileContainers_;
};

CMBIPC_EXPORT QDebug operator<<(QDebug debug, const RequestSourceRangesAndDiagnosticsForQueryMessage &message);
void PrintTo(const RequestSourceRangesAndDiagnosticsForQueryMessage &message, ::std::ostream* os);

DECLARE_MESSAGE(RequestSourceRangesAndDiagnosticsForQueryMessage)

} // namespace ClangBackEnd