#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 50    
#define RULE1_DIVIDE 100.f
#define RULE2_DISTANCE 200.f
#define RULE3_DIVIDE 8.f

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 150.f;
            location.Y = FMath::Cos(incr * (i + AGENT_COUNT / 2)) * 150.f;
            location.Z = FMath::Cos(incr * i) * 150.f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

FVector UFlockingManager::rule1(int j) {
    AAgent* b = Agents[j];
    FVector pcj = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != j) {
            pcj += Agents[i]->GetActorLocation();
        }
    }
    pcj /= AGENT_COUNT - 1;
    return (pcj - b->GetActorLocation()) / RULE1_DIVIDE;
}

FVector UFlockingManager::rule2(int j) {
    AAgent* b = Agents[j];
    FVector c = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        FVector diff = b->GetActorLocation() - Agents[i]->GetActorLocation();
        if (i != j && diff.Size() < RULE2_DISTANCE) {
            c += diff;
        }
    }
    return c;
}

FVector UFlockingManager::rule3(int j) {
    AAgent* b = Agents[j];
    FVector pvj = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != j) {
            pvj += b->Velocity;
        }
    }
    pvj /= AGENT_COUNT - 1;
    return (pvj - b->Velocity) / RULE3_DIVIDE;
}

void UFlockingManager::Flock() {
    for (int i = 0; i < AGENT_COUNT; i++) {
        Agents[i]->Velocity += rule1(i);
        Agents[i]->Velocity += rule2(i);
        Agents[i]->Velocity += rule3(i);
    }
}