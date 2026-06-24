
#include "PersistenceService.h"

PersistenceService::PersistenceService(WateringController &ctrl,
                                       IEEPROMWriter &w,
                                       IEEPROMReader &r)
    : watering(ctrl), writer(w), reader(r)
{
}

bool PersistenceService::save()
{
    writer.seek(0);

    // Version
    writer.writeByte(VERSION_MAJOR);
    writer.writeByte(VERSION_MINOR);

    // Save programs
    for (uint8_t i = 0; i < 8; i++)
    {
        auto &p = watering.getProgram(i);

        writer.writeEnum(static_cast<uint8_t>(p.mode));
        writer.writeUInt32(p.frequency);
        writer.writeUInt32(p.duration);
        writer.writeUInt32(p.startTime);
    }

    return true;
}

bool PersistenceService::load(uint32_t now)
{
    reader.seek(0);

    uint8_t major = reader.readByte();
    uint8_t minor = reader.readByte();

    // compatibility check
    if (major > VERSION_MAJOR)
        return false; // incompatible future version

    for (uint8_t i = 0; i < 8; i++)
    {
        ValveProgram p;

        p.mode = reader.readEnum<ValveMode>();
        p.frequency = reader.readUInt32();
        p.duration = reader.readUInt32();
        p.startTime = reader.readUInt32();

        watering.updateProgram(i, p, now);
    }

    return true;
}
