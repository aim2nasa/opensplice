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
#ifndef OSPL_DDS_CORE_COND_TREADCONDITION_IMPL_HPP_
#define OSPL_DDS_CORE_COND_TREADCONDITION_IMPL_HPP_

/**
 * @file
 */

/*
 * OMG PSM class declaration
 */
#include <dds/sub/cond/TReadCondition.hpp>
#include <org/opensplice/sub/cond/ReadConditionDelegate.hpp>

// Implementation

namespace dds
{
namespace sub
{
namespace cond
{

template <typename DELEGATE>
TReadCondition<DELEGATE>::TReadCondition(
    const dds::sub::AnyDataReader& dr,
    const dds::sub::status::DataState& status)
{
    ISOCPP_REPORT_STACK_DDS_BEGIN(dr);
    this->set_ref(new DELEGATE(dr, status));
	this->delegate()->init(this->impl_);
}

/** @cond
 * Somehow, these cause functions duplicates in doxygen documentation.
 */
template <typename DELEGATE>
template <typename FUN>
TReadCondition<DELEGATE>::TReadCondition(
        const dds::sub::AnyDataReader& dr,
        const dds::sub::status::DataState& status,
        FUN& functor)
{
	ISOCPP_REPORT_STACK_DDS_BEGIN(dr);
    this->set_ref(new DELEGATE(dr, status));
	this->delegate()->init(this->impl_);
    this->delegate()->set_handler(functor);
}

template <typename DELEGATE>
template <typename FUN>
TReadCondition<DELEGATE>::TReadCondition(
        const dds::sub::AnyDataReader& dr,
        const dds::sub::status::DataState& status,
        const FUN& functor)
{
	ISOCPP_REPORT_STACK_DDS_BEGIN(dr);
    this->set_ref(new DELEGATE(dr, status));
    this->delegate()->init(this->impl_);
    this->delegate()->set_handler(functor);
}
/** @endcond */

template <typename DELEGATE>
TReadCondition<DELEGATE>::~TReadCondition() { }

template <typename DELEGATE>
const dds::sub::status::DataState TReadCondition<DELEGATE>::state_filter() const
{
    ISOCPP_REPORT_STACK_DDS_BEGIN(*this);
    return this->delegate()->state_filter();
}

template <typename DELEGATE>
const AnyDataReader& TReadCondition<DELEGATE>::data_reader() const
{
    ISOCPP_REPORT_STACK_DDS_BEGIN(*this);
    return this->delegate()->data_reader();
}

}
}
namespace core
{
namespace cond
{
template <typename DELEGATE>
TCondition<DELEGATE>::TCondition(const dds::sub::cond::TReadCondition<org::opensplice::sub::cond::ReadConditionDelegate>& h)
{
    if (h.is_nil()) {
        /* We got a null object and are not really able to do a typecheck here. */
        /* So, just set a null object. */
        *this = dds::core::null;
    } else {
        this->::dds::core::Reference<DELEGATE>::impl_ = OSPL_CXX11_STD_MODULE::dynamic_pointer_cast<DELEGATE_T>(h.delegate());
        if (h.delegate() != this->::dds::core::Reference<DELEGATE>::impl_) {
            throw dds::core::IllegalOperationError(std::string("Attempted invalid cast: ") + typeid(h).name() + " to " + typeid(*this).name());
        }
    }
}

template <typename DELEGATE>
TCondition<DELEGATE>&
TCondition<DELEGATE>::operator=(const dds::sub::cond::TReadCondition<org::opensplice::sub::cond::ReadConditionDelegate>& rhs)
{
    if (this != (TCondition*)&rhs) {
        if (rhs.is_nil()) {
            /* We got a null object and are not really able to do a typecheck here. */
            /* So, just set a null object. */
            *this = dds::core::null;
        } else {
            TCondition other(rhs);
            /* Dont have to copy when the delegate is the same. */
            if (other.delegate() != this->::dds::core::Reference<DELEGATE>::impl_) {
                *this = other;
            }
        }
    }
    return *this;
}
}
}
}
// End of implementation

#endif /* OSPL_DDS_CORE_COND_TREADCONDITION_IMPL_HPP_ */
