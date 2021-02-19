//
// Created by Percebe64 on 2/17/2021.
//

#ifndef QUESTER_QPROJECT_HXX
#define QUESTER_QPROJECT_HXX

#include <Poco/UUIDGenerator.h>
#include <Poco/Path.h>
#include <Core/QGlobals.hxx>

#include <Core/QCharacter.hxx>
#include <Core/QDialogue.hxx>
#include <Core/Quest.hxx>
#include <vector>

class QProject {
public:
    QProject();
    QProject(const char* path, std::string& name, std::string& ue4Version, std::string& description);
    explicit QProject(const Poco::UUID& uuid);
    ~QProject() = default;

    bool operator==(const QProject& otherProject) noexcept {
        return ( GetUUID() == otherProject.GetUUID() );
    }

    bool operator!=(const QProject& otherProject) noexcept {
        return ( GetUUID() != otherProject.GetUUID() );
    }

    [[nodiscard]] Poco::UUID  GetUUID() const;
    [[nodiscard]] Poco::Path  GetPath() const;
    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] std::string GetUE4Version() const;
    [[nodiscard]] std::string GetDescription() const;

    void SetPath(const std::string& path);
    void SetPath(const Poco::Path& path);
    void SetName(const std::string& name);
    void SetUE4Version(const std::string& ue4V);
    void SetDescription(const std::string& description);


private:
    Poco::UUID       _uuid;
    Poco::Path       _path;
    std::string      _name;
    std::string      _ue4Version;
    std::string      _description;

    std::vector<Quest*> _quests;
    std::vector<QDialogue*> _dialogues;

};
#endif //QUESTER_QPROJECT_HXX
