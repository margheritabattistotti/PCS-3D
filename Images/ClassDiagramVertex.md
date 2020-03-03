```plantuml
@startuml

package Eigen <<Rectangle>> {
    class Vector3d
}

package Gedim <<Rectangle>> {
    class Vertex
}

Vector3d <|- Vertex

@enduml
```