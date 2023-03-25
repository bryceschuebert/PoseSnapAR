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


#ifndef _Base_ImportError_HeaderFile
#define _Base_ImportError_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_READER_STATISTICS
#include <cadex/Base_Allocator.hxx>
#include <memory>

namespace cadex {
class Base_UTF16String;
namespace internal {
class Base_ImportErrorImpl;
}

class Base_ImportError
{
public:
    __CADEX_DEFINE_MEMORY_MANAGEMENT
    __CADEX_EXPORT Base_ImportError (const std::shared_ptr <internal::Base_ImportErrorImpl>& theImpl);

    __CADEX_EXPORT const Base_UTF16String& Message() const;
    __CADEX_EXPORT const Base_UTF16String& Context() const;

    internal::Base_ImportErrorImpl* Impl() const { return myImpl.get(); }
private:
    std::shared_ptr <internal::Base_ImportErrorImpl> myImpl;
};

}

#endif
#endif
