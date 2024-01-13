"""
might be cool to try sth like this -- brush up on classical mechanics

Our most popular missiles today,
all of which are obscenely expensive
(apparently mainly due to their hyper-precise guidance systems)
are:
  * Ones we hope to use never
    * Minuteman (ICBM)
    * Trident (SLBM)
  * Ones we do use all the time
    * Tomahawk (SSM/Cruise)
    * Patriot (SAM)
    * Hellfire (ASM)
"""

from collections.abc import Sequence
import dataclasses
import datetime


@dataclasses.dataclass(kw_only=True, frozen=True)
class Coordinate:
    latitude: int = 0
    longitude: int = 0
    altitude: int = 0


@dataclasses.dataclass(kw_only=True, frozen=True)
class GeoZone:
    """Connect coordinates with straight lines. Assumed to include land + airspace."""
    coordinates: Sequence[coordinates]

    def __post_init__(self) -> None:
        for coordinate in self.coordinates:
            if coordinate.altitude != 0:
                raise ValueError("GeoZone automatically assumed to include land + airspace. Altitude is meaningless here.")

    def __contains__(self, coordinate: Coordinate) -> bool:
        """Tell whether given coordinate falls within the GeoZone."""
        ...


@dataclasses.dataclass(kw_only=True, frozen=True)
class Vector:
    """Considered using spherical coordinates, but it doesn't really seem to help for an object in freefall."""
    r: float = 0  # magnitude
    # direction:
    x: float = 2**0.5  # along latitude tangent line
    y: float = 2**0.5  # along longitude tangent line
    # lat and long tangent lines are orthogonal, so their cross product is this direction:
    z: float = 0  # perpendicular to surface

    def __post_init__(self) -> None:
        u = (x**2 + y**2 + z**2)**0.5
        if abs(u - 1) > 1e-6:
            raise ValueError(f"Direction should be unit vector, ({self.x}, {self.y}, {self.z}) implies {u}!")


@dataclasses.dataclass(kw_only=True, frozen=True)
class Velocity:
    """Directed velocity in m/s. Speed assumed to be <<< speed of light in a vacuum."""
    v: Vector

    def __post_init__(self) -> None:
        # be conservative
        if self.v.r > 3e8/100:
            raise NotImplementedError(f"Relativistic effects will kick in at {self.v.r}m/s!")


@dataclasses.dataclass(kw_only=True, frozen=True)
class Acceleration:
    """Directed acceleration in m/s^2."""
    a: Vector


@dataclasses.dataclass(kw_only=True, frozen=True)
class Threat:
    """
    Assume a threat is detected at an exact location and velocity, in freefall.
    Its location will evolve according to inertia + gravity.

    Potential extensions:
        - Assume you can't fully triangulate an exact single location
        - Allow non-freefall (so, factor in non-gravitational acceleration + higher moments)
        - Factor in air resistance given warhead shape
    """
    timestamp: datetime.datetime
    coordinate: Coordinate
    velocity: Velocity
    freefall: bool = True

    def locate_at(timestamp: datetime.datetime | None = None) -> Coordinate:
        """Tell where this threat has moved to by the given timestamp, according to inertia + gravity."""
        if timestamp is None:
            # really should add like the 5ms or whatever it will take for this to run...
            timestamp = datetime.datetime.now()
        if not self.freefall:
            raise NotImplementedError(self.freefall)
        ...


@dataclasses.dataclass(kw_only=True, frozen=True)
class Interceptor:
    # kg
    mass: float = 1_000
    # N
    force: Vector


def get_best_interceptor(threat: Threat, geo_zone: GeoZone) -> Interceptor:
    """
    If we accelerate an interceptor over-forcefully at the threat, we'll waste energy.
    But if we accelerate it under-forcefully, we won't intercept it in time.
    So (for now assuming the interceptor weights 1,000kg), what is the min force we can spend?
    Thus "best" is used as in "best unbiased linear estimator", that is, meaning "most efficient".
    """
    ...
