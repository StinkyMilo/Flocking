#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 10    
#define RULE1_DIVIDE 100.f
#define RULE2_DISTANCE 100.f
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
            location.Z = FMath::Cos(incr * i) * 150.f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

FVector UFlockingManager::rule1(AAgent * b) {
    FVector pcj = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (b != Agents[i]) {
            pcj += Agents[i]->GetActorLocation();
        }
    }
    pcj /= AGENT_COUNT - 1;
    return (pcj - b->GetActorLocation()) / RULE1_DIVIDE;
}

FVector UFlockingManager::rule2(AAgent * b) {
    FVector c = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        FVector diff = b->GetActorLocation() - Agents[i]->GetActorLocation();
        if (b != Agents[i] && diff.Size() < RULE2_DISTANCE) {
            c -= diff;
        }
    }
    return c;
}

FVector UFlockingManager::rule3(AAgent * b) {
    FVector pvj = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (b != Agents[i]) {
            pvj += b->Velocity;
        }
    }
    pvj /= AGENT_COUNT - 1;
    return (pvj - b->Velocity) / RULE3_DIVIDE;
}

void UFlockingManager::Flock() {
    for (int i = 0; i < AGENT_COUNT; i++) {
        Agents[i]->Velocity += rule1(Agents[i]);
        Agents[i]->Velocity += rule2(Agents[i]);
        Agents[i]->Velocity += rule3(Agents[i]);
    }
}