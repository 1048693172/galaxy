/* ------------------------------------------------------------------
 * Copyright (C) 1998-2010 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
#define IMPLEMENT_TrackFragmentRandomAccessAtom

#include "trackfragmentrandomaccessatom.h"
#include "oscl_int64_utils.h"

typedef Oscl_Vector<PVA_FF_RandomAccessEntry, OsclMemAllocator> PVA_FF_RandomAccessEntryVecType;

// constructor
PVA_FF_TfraAtom::PVA_FF_TfraAtom(uint32 trackId, uint8 version)
        : PVA_FF_FullAtom(TRACK_FRAGMENT_RANDOM_ACCESS_ATOM, version, (uint32)0)
{
    _trackId = trackId;
    _reserved = TFRA_LENGTH_SIZE;
    _entryCount = 0;

    _moofUpdateSample = 1;

    // initialise vectors
    PV_MP4_FF_NEW(fp->auditCB, PVA_FF_RandomAccessEntryVecType, (), _pSampleEntries);

    recomputeSize();
}


// destructor
PVA_FF_TfraAtom::~PVA_FF_TfraAtom()
{

    PV_MP4_FF_TEMPLATED_DELETE(NULL, PVA_FF_RandomAccessEntryVecType, Oscl_Vector, _pSampleEntries);
}



// add new entry to TFRA
void
PVA_FF_TfraAtom::addSampleEntry(uint64 ts, uint64 moofOffset, uint32 trafNumber,
                                uint32 trunNumber, uint32 sampleNumber)
{
    PVA_FF_RandomAccessEntry sampleEntry;
    sampleEntry.time            = ts;
    sampleEntry.moofOffset      = moofOffset;
    sampleEntry.trafNumber      = trafNumber;
    sampleEntry.trunNumber      = trunNumber;
    sampleEntry.sampleNumber    = sampleNumber;

    _pSampleEntries->push_back(sampleEntry) ;

    _entryCount++;

    recomputeSize();
}


uint32
PVA_FF_TfraAtom::getTrackId()
{
    return  _trackId;
}

uint32
PVA_FF_TfraAtom::getEntryCount()
{
    return  _entryCount;
}


// for last moof all random entries are updated
// by given offset
void
PVA_FF_TfraAtom::updateMoofOffset(uint32 offset)
{
    if (_pSampleEntries->size() >= _entryCount)
    {
        if (_moofUpdateSample <= _entryCount)
        {
            for (uint32 ii = _moofUpdateSample; ii <= _entryCount; ii++)
            {
                ((*_pSampleEntries)[ii-1].moofOffset) += offset;
            }
            _moofUpdateSample = _entryCount + 1;
        }
    }
}


// recompute size of atom
void
PVA_FF_TfraAtom::recomputeSize()
{
    int32 size = getDefaultSize();

    size += 4;  // track id
    size += 4;  // reserved
    size += 4;  // entry count

    // calculate the rand. access table size
    int32 entrysize = 0;
    if (getVersion() == 0)
    {
        entrysize += 4;  // time
        entrysize += 4;  // MoofOffset
    }
    else
    {
        entrysize += 8;  // time
        entrysize += 8;  // MoofOffset
    }

    entrysize += 2;  // traf number
    entrysize += 2;  // trun number
    entrysize += 2;  // sample number

    size += entrysize * (_entryCount);
    _size = size;

    // Update the parent atom size
    if (_pparent != NULL)
    {
        _pparent->recomputeSize();
    }
}


// write atom to target file
bool
PVA_FF_TfraAtom::renderToFileStream(MP4_AUTHOR_FF_FILE_IO_WRAP* fp)
{
    uint32 rendered = 0;

    if (!renderAtomBaseMembers(fp))
    {
        return false;
    }
    rendered += getDefaultSize();

    if (!PVA_FF_AtomUtils::render32(fp, _trackId))
    {
        return false;
    }
    rendered += 4;

    if (!PVA_FF_AtomUtils::render32(fp, _reserved))
    {
        return false;
    }
    rendered += 4;

    if (!PVA_FF_AtomUtils::render32(fp, _entryCount))
    {
        return false;
    }
    rendered += 4;

    for (uint32 ii = 0; ii < _entryCount; ii++)
    {

        if (getVersion() == 0)
        {
            if (!PVA_FF_AtomUtils::render32(fp,
                                            Oscl_Int64_Utils::get_uint64_lower32((*_pSampleEntries)[ii].time)))
            {
                return false;
            }
            rendered += 4;

            if (!PVA_FF_AtomUtils::render32(fp,
                                            Oscl_Int64_Utils::get_uint64_lower32((*_pSampleEntries)[ii].moofOffset)))
            {
                return false;
            }
            rendered += 4;
        }
        else
        {
            if (!PVA_FF_AtomUtils::render64(fp, (*_pSampleEntries)[ii].time))
            {
                return false;
            }
            rendered += 8;

            if (!PVA_FF_AtomUtils::render64(fp, (*_pSampleEntries)[ii].moofOffset))
            {
                return false;
            }
            rendered += 8;
        }

        if (!PVA_FF_AtomUtils::render16(fp, (*_pSampleEntries)[ii].trafNumber))
        {
            return false;
        }
        rendered += 2;

        if (!PVA_FF_AtomUtils::render16(fp, (*_pSampleEntries)[ii].trunNumber))
        {
            return false;
        }
        rendered += 2;

        if (!PVA_FF_AtomUtils::render16(fp, (*_pSampleEntries)[ii].sampleNumber))
        {
            return false;
        }
        rendered += 2;
    }
    return true;
}
