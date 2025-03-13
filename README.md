# Introduce
An Unreal Engine plugin that supports ActiveMQ producers and consumers.

# About ActiveMQ-cpp
This plugin uses a modified version of the ActiveMQ-cpp library, not the original Apache branch. To support C++17/20, the code has been altered and can be found at [https://github.com/hl1282456555/activemq-cpp/tree/3.9.x](https://github.com/hl1282456555/activemq-cpp/tree/3.9.x).

# Project Details
 To support blueprint calls, all classes inherit from UObject, so you need to pay attention to lifecycle management when using them. 
 
 UActiveMQSubsystem::CreateConnection is used to create a connection, which is the starting point of all processes.

# TODO
- [x] Wrap all interfaces in activemq-cpp that return STL types with `std::shared_ptr`
- [ ] Wrap `char`, `short`, and `unsigned short` to support interfaces that are currently inaccessible in Blueprints

# Example
 ```cpp
    UActiveMQSubsystem* Subsystem = World->GetSubsystem<UActiveMQSubsystem>();
    if (Subsystem == nullptr)
    {
        return;
    }

    Connection = Subsystem->CreateConnection(TEXT("broker uri"), TEXT("username"), TEXT("password"));
    if (Connection == nullptr)
    {
        return;
    }

    Connection->Start();

    Session = Connection->CreateSession();
    if (Session == nullptr)
    {
        return;
    }

    if (bUseTopic)
    {
        Destination = Session->CreateTopic(TEXT("Topic Name"));
    }
    else
    {
        Destination = Session->CreateQueue(TEXT("Queue Name"));
    }

    if (Destination == nullptr)
    {
        return;
    }

    Consumer = Session->CreateConsumer(Destination);
    if (Consumer == nullptr)
    {
        return;
    }

    // Bind a delegate for receive messages from this consumer asynchronously.
    Consumer->OnReceivedMessage.AddDynamic(Object, &ObjectClass::Function);
 ```
