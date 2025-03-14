/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _CMS_TOPIC_
#define _CMS_TOPIC_

#include <cms/Config.h>
#include <cms/Destination.h>
#include <cms/CMSException.h>

namespace cms {

    /**
     * An interface encapsulating a provider-specific topic name.
     *
     * A Topic is a Publish / Subscribe type Destination.  All Messages sent to a Topic are
     * broadcast to all Subscribers of that Topic unless the Subscriber defines a Message
     * selector that filters out that Message.
     *
     * @since 1.0
     */
    class CMS_API Topic : public Destination {
    public:

        virtual ~Topic();

        /**
         * Gets the name of this topic.
         *
         * @return The topic name.
         *
         * @throws CMSException - If an internal error occurs.
         */
        virtual std::shared_ptr<std::string> getTopicName() const = 0;

    };

}

#endif /*_CMS_TOPIC_*/
