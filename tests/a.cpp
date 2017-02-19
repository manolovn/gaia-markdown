/*
 * Copyright 2017 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "a.h"

#include <qtest_kde.h>

QTEST_KDEMAIN ( a, NoGUI );

void a::initTestCase() {
    // Called before the first testfunction is executed
}

void a::cleanupTestCase() {
    // Called after the last testfunction was executed
}

void a::init() {
    // Called before each testfunction is executed
}

void a::cleanup() {
    // Called after every testfunction
}

void a::doSomething() {
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

#include "a.moc"
