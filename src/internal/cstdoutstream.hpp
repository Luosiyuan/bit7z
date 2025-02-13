/*
 * bit7z - A C++ static library to interface with the 7-zip shared libraries.
 * Copyright (c) 2014-2022 Riccardo Ostani - All Rights Reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef CSTDOUTSTREAM_HPP
#define CSTDOUTSTREAM_HPP

#include <ostream>
#include <cstdint>

#include "internal/guids.hpp"
#include "internal/macros.hpp"

#include <7zip/IStream.h>
#include <Common/MyCom.h>

namespace bit7z {

using std::ostream;

class CStdOutStream : public IOutStream, public CMyUnknownImp {
    public:
        explicit CStdOutStream( std::ostream& outputStream );

        CStdOutStream( const CStdOutStream& ) = delete;

        CStdOutStream( CStdOutStream&& ) = delete;

        CStdOutStream& operator=( const CStdOutStream& ) = delete;

        CStdOutStream& operator=( CStdOutStream&& ) = delete;

        MY_UNKNOWN_VIRTUAL_DESTRUCTOR( ~CStdOutStream() ) = default;

        MY_UNKNOWN_IMP1( IOutStream ) // NOLINT(modernize-use-noexcept)

        // IOutStream
        BIT7Z_STDMETHOD( Write, void const* data, UInt32 size, UInt32* processedSize );

        BIT7Z_STDMETHOD( Seek, Int64 offset, UInt32 seekOrigin, UInt64* newPosition );

        BIT7Z_STDMETHOD( SetSize, UInt64 newSize );

    private:
        ostream& mOutputStream;
};

}  // namespace bit7z

#endif // CSTDOUTSTREAM_HPP
