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


#ifndef _ModelData_ModelReader_HeaderFile
#define _ModelData_ModelReader_HeaderFile

#include <cadex/ModelData_Model.hxx>
#include <cadex/Base_UTF16String.hxx>

namespace cadex {
class Base_ReaderParameters;
namespace internal {
class ModelData_ModelReaderImpl;
}

class ModelData_ModelReader
{
public:

    __CADEX_EXPORT ModelData_ModelReader();
    __CADEX_EXPORT ~ModelData_ModelReader();

    __CADEX_EXPORT bool Read (const Base_UTF16String& theFilePath, ModelData_Model& theModel);

    __CADEX_EXPORT void SetReaderParameters (const Base_ReaderParameters& theParameters);

    __CADEX_EXPORT void SetProgressStatus (const Base_ProgressStatus& theProgressStatus);
    __CADEX_EXPORT const Base_ProgressStatus& ProgressStatus() const;

    internal::ModelData_ModelReaderImpl* Impl() { return myImpl.get(); }

private:
    std::shared_ptr<internal::ModelData_ModelReaderImpl>  myImpl;
};

}
#endif
