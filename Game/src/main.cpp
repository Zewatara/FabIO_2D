#include <Engine/Application.h>

#include <glad/glad.h>
#include <box2d/box2d.h>
#include <glm/glm.hpp>

class MyGame : public Engine::Application {
public:
    MyGame() : Application({"Game", 1280, 720, true}) {}

protected:
    void OnInit() override {
        // Smoke test: Box2D and GLM are linked and usable.
        b2WorldDef def = b2DefaultWorldDef();
        m_world = b2CreateWorld(&def);
        m_clear = glm::vec3(0.1f, 0.1f, 0.15f);
    }

    void OnUpdate(float dt) override { b2World_Step(m_world, dt, 4); }

    void OnRender() override {
        glClearColor(m_clear.r, m_clear.g, m_clear.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OnShutdown() override { b2DestroyWorld(m_world); }

private:
    b2WorldId m_world{};
    glm::vec3 m_clear{};
};

int main() {
    MyGame game;
    return game.Run();
}
