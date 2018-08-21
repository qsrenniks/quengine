#include "stdafx.h"
#include "SerializationTesting.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>

SerializationTesting::SerializationTesting()
{
  
}

SerializationTesting::~SerializationTesting()
{

 }

void SerializationTesting::Update(float dt)
{ 
  health += dt;
}

void SerializationTesting::Serialize(rapidjson::Document& doc)
{
  IGameObject::Serialize(doc);

  using namespace rapidjson;

  Value object(kObjectType);
  //object.SetObject();
  //object.SetString("GameObject");
  object.AddMember("Health", health, doc.GetAllocator());

  doc.AddMember("CerealTest", object, doc.GetAllocator());
}

void SerializationTesting::Deserialize(rapidjson::Document& doc)
{
  IGameObject::Deserialize(doc);

  auto val = doc.FindMember("CerealTest");

  if (val->value.IsObject() == true)
  {
    health = val->value.GetObjectA().FindMember("Health")->value.GetFloat();
  }

}
