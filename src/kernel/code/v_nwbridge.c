/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to TO_YEAR PrismTech
 *   Limited, its affiliated companies and licensors. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */
#include "v_nwbridge.h"
#include "v__statCat.h"
#if 0
#include "v_nwbridgeStatistics.h"
#endif
#include "v_service.h"
#include "v__groupInstance.h"
#include "v_group.h"
#include "v__kernel.h"
#include "v_participant.h"
#include "os_report.h"

v_nwbridge
v_nwbridgeNew(
    v_kernel kernel,
    const c_char *name,
    const c_char *extStateName,
    v_participantQos qos,
    c_bool enable)
{
    v_nwbridge s;
    v_participantQos q;

    assert(C_TYPECHECK(kernel, v_kernel));
    assert(name != NULL);

    q = v_participantQosNew(kernel, qos);
    if (q == NULL) {
        OS_REPORT(OS_ERROR, "v_nwbridgeNew", V_RESULT_INTERNAL_ERROR,
                  "nwbridge service not created: inconsistent qos");
        s = NULL;
    } else {
        s = v_nwbridge(v_objectNew(kernel, K_NWBRIDGE));

#if 0
        if (v_isEnabledStatistics(kernel, V_STATCAT_NWBRIDGE)) {
            s->statistics = v_nwbridgeStatisticsNew(kernel);
        } else {
            s->statistics = NULL;
        }
#endif
        v_serviceInit(v_service(s), name, extStateName, V_SERVICETYPE_NWBRIDGE, q, enable);
        c_free(q);
        if (v_service(s)->state == NULL) {
            v_serviceFree(v_service(s));
            s = NULL;
        }
    }
    return s;
}

void
v_nwbridgeFree(
    v_nwbridge du)
{
    assert(C_TYPECHECK(du, v_nwbridge));
    v_serviceFree(v_service(du));
}

