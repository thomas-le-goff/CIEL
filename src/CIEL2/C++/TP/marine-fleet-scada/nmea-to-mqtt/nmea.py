import json

from abc import ABC, abstractmethod
from dataclasses import dataclass


@dataclass
class NMEAMessage(ABC):
    """Classe de base pour tous les messages NMEA."""

    talker_id: str
    message_type: str
    raw_data: str

    @classmethod
    @abstractmethod
    def parse(cls, nmea_str: str) -> "NMEAMessage":
        """Désérialise une trame NMEA en objet."""
        pass

    @abstractmethod
    def to_json(self) -> str:
        """Sérialise l'objet en JSON pour MQTT."""
        pass

    def _validate_checksum(self, nmea_str: str) -> bool:
        """Valide le checksum d'une trame NMEA."""
        return False


@dataclass
class GPRMC(NMEAMessage):
    """Classe pour les messages $GPRMC."""

    time: str = ""
    status: str = ""
    latitude: float = 0.0
    longitude: float = 0.0
    speed: float = 0.0
    course: float = 0.0
    date: str = ""
    variation: float = 0.0
    variation_dir: str = ""

    @classmethod
    def parse(cls, nmea_str: str) -> "GPRMC":
        """Exemple: $GPRMC,103401.45,A,5052.9898,N,00121.7808,W,12.0,90.0,260126,5.0,E*45"""
        if not nmea_str.startswith("$GPRMC"):
            raise ValueError("Not a GPRMC message.")

        obj = cls(talker_id="GP", message_type="RMC", raw_data=nmea_str)

        if not obj._validate_checksum(nmea_str):
            raise RuntimeError(f"Invalid checksum for trame: {nmea_str}")

        nmea_splitted = nmea_str.split(",")
        obj.time = nmea_splitted[1]
        obj.status = nmea_splitted[2]
        obj.latitude = GPRMC._parse_latlon(nmea_splitted[3], nmea_splitted[4])
        obj.longitude = GPRMC._parse_latlon(nmea_splitted[5], nmea_splitted[6])
        obj.speed = nmea_splitted[7]
        obj.course = nmea_splitted[8]
        obj.date = nmea_splitted[9]
        obj.variation = nmea_splitted[10]
        obj.variation_dir = nmea_splitted[11]

        return obj

    def to_json(self) -> str:
        """Retourne un dictionnaire pour MQTT."""
        return json.dumps(
            {
                "type": "GPRMC",
                "timestamp": f"{self.date}T{self.time}Z",
                "latitude": self.latitude,
                "longitude": self.longitude,
                "speed": self.speed,
                "course": self.course,
                "status": self.status,
            }
        )

    def _validate_checksum(self, nmea_str: str) -> bool:
        """Valide le checksum d'une trame NMEA GPRMC."""
        return True  # TODO

    @staticmethod
    def _parse_latlon(value: str, direction: str) -> float:
        """Convertit DDMM.MMMM en degrés décimaux."""
        degrees = float(value[:2])
        minutes = float(value[2:]) / 60
        result = degrees + minutes
        return -result if direction in ["W", "S"] else result
