from datetime import datetime
from enum import Enum

from pydantic import BaseModel, Field, ValidationError, model_validator


class Rank(str, Enum):
    CADET = "cadet"
    OFFICER = "officer"
    LIEUTENANT = "lieutenant"
    CAPTAIN = "captain"
    COMMANDER = "commander"


class CrewMember(BaseModel):
    member_id: str = Field(min_length=3, max_length=10)
    name: str = Field(min_length=2, max_length=50)
    rank: Rank
    age: int = Field(ge=18, le=80)
    specialization: str = Field(min_length=3, max_length=30)
    years_experience: int = Field(ge=0, le=50)
    is_active: bool = Field(default=True)


class SpaceMission(BaseModel):
    mission_id: str = Field(min_length=5, max_length=15)
    mission_name: str = Field(min_length=3, max_length=100)
    destination: str = Field(min_length=3, max_length=50)
    launch_date: datetime
    duration_days: int = Field(ge=1, le=3650)
    crew: list[CrewMember] = Field(min_length=1, max_length=12)
    mission_status: str = "planned"
    budget_millions: float = Field(ge=1.0, le=10000.0)

    @model_validator(mode="after")
    def validate_mission(self):
        if not self.mission_id.startswith("M"):
            raise ValueError(
                "Mission ID must start with M"
            )
    
        has_command = False
        for member in self.crew:
            if (
                member.rank == Rank.COMMANDER
                or member.rank == Rank.CAPTAIN
            ):
                has_command = True
        if not has_command:
            raise ValueError(
                "Mission must have at least one Commander or Captain"
            )

        if self.duration_days > 365:
            experienced = 0
            for member in self.crew:
                if member.years_experience >= 5:
                    experienced += 1
            experience_ratio = experienced / len(self.crew)
            if experience_ratio < 0.5:
                raise ValueError(
                    "Long missions require at least 50% experienced crew"
                )

        for member in self.crew:
            if not member.is_active:
                raise ValueError(
                    "All crew members must be active"
                )

        return self


def main() -> None:
    print("Space Mission Crew Validation")
    print("=========================================")

    mission = SpaceMission(
        mission_id="M2024_MARS",
        mission_name="Mars Colony Establishment",
        destination="Mars",
        launch_date="2026-07-20T00:00:00",
        duration_days=900,
        budget_millions=2500.0,
        crew=[
            CrewMember(
                member_id="C1",
                name="Sarah Connor",
                rank="commander",
                age=40,
                specialization="Mission Command",
                years_experience=15,
            ),
            CrewMember(
                member_id="C2",
                name="John Smith",
                rank="lieutenant",
                age=35,
                specialization="Navigation",
                years_experience=6,
            ),
            CrewMember(
                member_id="C3",
                name="Alice Johnson",
                rank="officer",
                age=30,
                specialization="Engineering",
                years_experience=8,
            ),
        ],
    )

    print("Valid mission created:")
    print(f"Mission: {mission.mission_name}")
    print(f"ID: {mission.mission_id}")
    print(f"Destination: {mission.destination}")
    print(f"Duration: {mission.duration_days} days")
    print(f"Budget: ${mission.budget_millions}M")
    print(f"Crew size: {len(mission.crew)}")

    print("Crew members:")

    for member in mission.crew:
        print(
            f"- {member.name} ({member.rank.value}) - "
            f"{member.specialization}"
        )

    print("=========================================")

    try:
        SpaceMission(
            mission_id="M2024_F",
            mission_name="Test Mission",
            destination="Hell",
            launch_date="2026-07-20T00:00:00",
            duration_days=100,
            budget_millions=1000,
            crew=[
                CrewMember(
                    member_id="C0",
                    name="Bob",
                    rank="officer",
                    age=30,
                    specialization="Plumber",
                    years_experience=5,
                )
            ],
        )

    except ValidationError as error:
        print("Expected validation error:")
        print(error.errors()[0]["msg"])


if __name__ == "__main__":
    main()
