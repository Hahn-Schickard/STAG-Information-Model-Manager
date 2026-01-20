# Adapter Management {#adapter_management}

@startuml
hide members

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
interface Listener as "**<<Event_Model>>**\nListener"
class AsyncListener as "**<<Event_Model>>**\nAsyncListener"

ModelRepository o-down- SourceInterface
SourceInterface <|.down. Source
Listener .left.> Source : uses
Listener <|.down. AsyncListener

abstract DataConsumerAdapter as "**<<Data_Consumer_Adapter>>**\nDataConsumerAdapter"
interface DataConnection as "**<<Data_Consumer_Adapter>>**\nDataConnection"
class DataConnector as "**<<Data_Consumer_Adapter>>**\nDataConnector"
class ListenerConnection as "**<<Information_Model_Manager>>**\nListenerConnection"

ModelRepository .right......> DataConnector : provides
DataConnector .down.> DataConnection : creates
DataConsumerAdapter .left.> DataConnector : uses
DataConnection <|.down. ListenerConnection
ListenerConnection .left.> Listener : uses
@enduml

