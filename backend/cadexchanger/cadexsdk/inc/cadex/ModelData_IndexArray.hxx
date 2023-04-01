#ifndef _ModelData_IndexArray_HeaderFile
#define _ModelData_IndexArray_HeaderFile

#include <cadex/Base_Macro.hxx>

#if __CADEX_PREVIEW_B_REP_TO_POLY_ASSOCIATIONS

namespace cadex {

namespace internal {
class ModelData_IndexArrayImpl;
}

class ModelData_IndexArray
{

public:
    typedef int IndexType;
       
    __CADEX_EXPORT ModelData_IndexArray();

    __CADEX_EXPORT size_t Size() const;
    __CADEX_EXPORT IndexType Element (size_t theIndex) const;
    IndexType operator[] (size_t theIndex) const { return Element (theIndex); }

    const std::shared_ptr<internal::ModelData_IndexArrayImpl>& Impl() const { return myImpl; }

private:
    std::shared_ptr<internal::ModelData_IndexArrayImpl> myImpl;
};

}

#endif

#endif
