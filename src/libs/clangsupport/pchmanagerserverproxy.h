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

#include "baseserverproxy.h"
#include "clangsupport_global.h"
#include "pchmanagerserverinterface.h"
#include "readmessageblock.h"
#include "writemessageblock.h"

#include <QtGlobal>

#include <memory>

QT_BEGIN_NAMESPACE
class QIODevice;
QT_END_NAMESPACE

namespace ClangBackEnd {

class PchManagerClientInterface;

class CLANGSUPPORT_EXPORT PchManagerServerProxy final : public BaseServerProxy,
                                                        public PchManagerServerInterface
{
public:
    explicit PchManagerServerProxy(PchManagerClientInterface *client, QIODevice *ioDevice);

    void end() override;
    void updatePchProjectParts(UpdatePchProjectPartsMessage &&message) override;
    void removePchProjectParts(RemovePchProjectPartsMessage &&message) override;
};

} // namespace ClangBackEnd
