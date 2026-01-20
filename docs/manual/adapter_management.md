# Adapter Management {#adapter_management}

The diagram bellow depicts how `Technology Adapters` and `Data Consumer Adapters` are used within the `Information_Model_Manager` as well as how the registered `Technology Adapter` and `Data Consumer Adapter` implementations communicate via the `Event Model`.

@startuml
hide members
skinparam minClassWidth 150

class ModelManager as "**<<Information_Model_Manager>>**\nModelManager"
interface RepositoryInterface as "**<<Technology_Adapter>>**\nModelRepository"
abstract TechnologyAdapter as "**<<Technology_Adapter>>**\nTechnologyAdapter"
class ModelRepository as "**<<Information_Model_Manager>>**\nModelRepository"

ModelManager o-- ModelRepository
ModelRepository .left.|> RepositoryInterface
TechnologyAdapter .right.> RepositoryInterface : uses
ModelManager ..> TechnologyAdapter : uses

interface SourceInterface as "**<<Event_Model>>**\nSourceInterface"
class Source as "**<<Event_Model>>**\nSource"
interface ListenerInterface as "**<<Event_Model>>**\nListenerInterface"
class AsyncListener as "**<<Event_Model>>**\nAsyncListener"

ModelRepository o-down- SourceInterface
SourceInterface <|.down. Source
ListenerInterface .left.> Source : uses
ListenerInterface <|.down. AsyncListener

abstract DataConsumerAdapter as "**<<Data_Consumer_Adapter>>**\nDataConsumerAdapter"
interface DataConnection as "**<<Data_Consumer_Adapter>>**\nDataConnection"
class DataConnector as "**<<Data_Consumer_Adapter>>**\nDataConnector"
class ListenerConnection as "**<<Information_Model_Manager>>**\nListenerConnection"

ModelManager ..> DataConnector : exposes
ModelRepository .right.> DataConnector : provides
DataConnector .down.> DataConnection : creates
DataConsumerAdapter .left.> DataConnector : uses
DataConnection <|.down. ListenerConnection
ListenerConnection .left.> ListenerInterface : uses
@enduml

