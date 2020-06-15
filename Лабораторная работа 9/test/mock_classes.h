#ifndef MOCK_CLASSES_H
#define MOCK_CLASSES_H

#include <gmock/gmock.h>
#include <../Lab9_Project_for_tests/IKeypad.h>
#include <../Lab9_Project_for_tests/ILatch.h>

class mock_IKeypad : public IKeypad {
public:
MOCK_METHOD(bool, isActive,(),(override));
MOCK_METHOD(void ,wait,(), (override));
MOCK_METHOD(PasswordResponse, requestPassword,(),(override));
};

class mock_ILatch : public ILatch {
public:
MOCK_METHOD(bool, isActive,(),(override));
MOCK_METHOD(DoorStatus, open,(),(override));
MOCK_METHOD(DoorStatus, close,(),(override) );
MOCK_METHOD(DoorStatus, getDoorStatus,(),(override));
};

#endif // MOCK_CLASSES_H
