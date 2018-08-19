#include "stdafx.h"
#include "SerializationTesting.h"


SerializationTesting::SerializationTesting()
{
  //read from file if it exists
}


SerializationTesting::~SerializationTesting()
{
  //write to file if it exists
}

void SerializationTesting::Update(float dt)
{ 
  health += dt;
}
