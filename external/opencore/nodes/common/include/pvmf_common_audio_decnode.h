/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
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
#ifndef PVMF_COMMON_AUDIO_DECNODE_H_INCLUDE
#define PVMF_COMMON_AUDIO_DECNODE_H_INCLUDE

#ifndef OSCL_BASE_H_INCLUDED
#include "oscl_base.h"
#endif

#ifndef OSCL_SCHEDULER_AO_H_INCLUDED
#include "oscl_scheduler_ao.h"
#endif

#ifndef PVMF_FORMAT_TYPE_H_INCLUDED
#include "pvmf_format_type.h"
#endif

#ifndef PVMF_NODE_INTERFACE_H_INCLUDED
#include "pvmf_node_interface.h"
#endif

#ifndef OSCL_PRIQUEUE_H_INCLUDED
#include "oscl_priqueue.h"
#endif

#ifndef PVMF_MEDIA_DATA_H_INCLUDED
#include "pvmf_media_data.h"
#endif




/* PVMF_MEDIA_CMD_BOC_FORMAT_ID
   format ID for beginning-of-clip messages to use with gapless
   playback.
   Format-specific info (uint32): number of samples to skip
   at the beginning of the next media data frame.
*/
struct BOCInfo
{
    uint32 samplesToSkip;
};

/* PVMF_MEDIA_CMD_EOC_FORMAT_ID
   format ID for end-of-clip messages to use with gapless
   playback.
   Format-specific info contains two 32-bit values:
      (uint32): number of frames that will follow this message.
      (uint32): number of samples to skip.
*/

struct EOCInfo
{
    uint32 framesToFollow;
    uint32 samplesToSkip;
};


#endif
