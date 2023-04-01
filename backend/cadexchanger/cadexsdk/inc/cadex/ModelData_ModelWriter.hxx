// ****************************************************************************
// $Id$
//
// Copyright (C) 2008-2014, Roman Lygin. All rights reserved.
// Copyright (C) 2014-2023, CADEX. All rights reserved.
//
// This file is part of the CAD Exchanger software.
//
// This file may be used under the terms and conditions of the License
// Agreement supplied with the software.
//
// This file is provided "AS IS" WITH NO WARRANTY OF ANY KIND, EITHER EXPRESSED
// OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE WARRANTY OF DESIGN,
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// ****************************************************************************


#ifndef _ModelData_ModelWriter_HeaderFile
#define _ModelData_ModelWriter_HeaderFile

#include <cadex/ModelData_Model.hxx>
#include <cadex/Base_UTF16String.hxx>

namespace cadex {
class Base_WriterParameters;
namespace internal {
class ModelData_ModelWriterImpl;
}

class ModelData_ModelWriter
{
public:

    __CADEX_EXPORT ModelData_ModelWriter();
    __CADEX_EXPORT ~ModelData_ModelWriter();

    __CADEX_EXPORT bool Write (const ModelData_Model& theModel, const Base_UTF16String& theFilePath);

    __CADEX_EXPORT void SetWriterParameters (const Base_WriterParameters& theParameters);

    __CADEX_EXPORT void SetProgressStatus (const Base_ProgressStatus& theProgressStatus);
    __CADEX_EXPORT const Base_ProgressStatus& ProgressStatus() const;

private:
    std::shared_ptr<internal::ModelData_ModelWriterImpl>  myImpl;
};

}
#endif

