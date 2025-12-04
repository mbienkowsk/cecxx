from enum import Enum
from typing import override


class CECEdition(Enum):
    """CEC editions supported by cecxx"""

    CEC_2013 = 2013
    CEC_2014 = 2014
    CEC_2017 = 2017

    def optimum_for_function(self, number: int):
        match self.value:
            case 2013:
                return number * 100 - 1500 if number <= 14 else number * 100 - 1400
            case 2014 | 2017:
                # FIXME: figure out what this looks like after F2 removal
                return number * 100

    @override
    def __str__(self) -> str:
        return f"CEC{self.value}"
