#ifndef RTD_H
#define RTD_H

#include <stdint.h>

enum RtdType {
    RTD_PT100 = 0,
    RTD_PT1000 = 1
};

class rtd {
public:
    rtd(enum RtdType type = RTD_PT100);

    void setType(enum RtdType type);
    enum RtdType getType() const;

    // Convert RTD resistance (scaled by 100) to temperature.
    float celsius(uint16_t ohmsX100);
    float celsius(float rtd_ohms);

    // Convert temperature in Celsius to RTD resistance (ohms)
    float celsius_to_rtd_ohms(float celsius);

    // Alternative methods (based on CVD or polynomial approximations)
    float celsius_cvd(float R_ohms);
    float celsius_cubic(float R_ohms);
    float celsius_polynomial(float R_ohms);
    float celsius_rationalpolynomial(float R_ohms);

private:
    enum RtdType _rtdType;
    float _nominalResistance;

    // Binary search in the lookup table
    int search_rtd_list(uint16_t ohmsX100);

    float ohmsX100_to_celsius(uint16_t ohmsX100);

    uint16_t scale_resistance(uint16_t ohmsX100);
    float scale_resistance(float ohms);

    uint16_t inverse_scale_resistance(uint16_t ohmsX100);
    float inverse_scale_resistance(float ohms);
};


extern const uint16_t Pt100_table[]; // cause I'd rather die than have static tables in my class definition.

#endif // RTD_H
