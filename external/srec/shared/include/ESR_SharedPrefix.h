/*---------------------------------------------------------------------------*
 *  ESR_SharedPrefix.h  *
 *                                                                           *
 *  Copyright 2007, 2008 Nuance Communciations, Inc.                               *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the 'License');          *
 *  you may not use this file except in compliance with the License.         *
 *                                                                           *
 *  You may obtain a copy of the License at                                  *
 *      http://www.apache.org/licenses/LICENSE-2.0                           *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an 'AS IS' BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. * 
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __ESR_SHAREDPREFIX_H
#define __ESR_SHAREDPREFIX_H



#include "PortExport.h"

#ifdef ESR_SHARED_EXPORTS
#define ESR_SHARED_API PORT_EXPORT_DECL
#else
#define ESR_SHARED_API PORT_IMPORT_DECL
#endif

#endif /* __ESR_SHAREDPREFIX_H */
