#pragma once

class IVisible
{
    bool m_visible;

public:
    IVisible()
        : m_visible(true)
    {
    }

    void setVisible(bool visible)
    {
        m_visible = visible;
    }

    bool getVisible() const
    {
        return m_visible;
    }
};
