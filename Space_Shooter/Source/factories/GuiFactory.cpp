#include "pch.h"
#include "GuiFactory.h"
#include "Widget.h"
#include "Image.h"
#include "Button.h"
#include "Label.h"


GuiFactory::GuiFactory()
	: m_sharedContext{ nullptr }
{
}

GuiFactory& GuiFactory::GetInstance()
{
	static GuiFactory instance;
	return instance;
}

std::vector<std::unique_ptr<Image>>  GuiFactory::CreateImages(const std::string& aType)
{
	rapidjson::Document document;
	ParseDocument(document);

	std::vector<std::unique_ptr<Image>> images;

	auto interfaceObject = document[aType.c_str()].GetObject();
	for (auto& imageObj : interfaceObject["images"].GetArray())
	{
		auto image = std::make_unique<Image>(m_sharedContext->m_window, m_sharedContext->m_textures.GetResource(imageObj["name"].GetString()));
		image->SetPosition({ imageObj["position"]["x"].GetFloat(), imageObj["position"]["y"].GetFloat() });
		image->SetScale({ imageObj["scale"]["x"].GetFloat(), imageObj["scale"]["y"].GetFloat() });

		images.push_back(std::move(image));
	}
	return images;
}

std::vector<std::unique_ptr<Label>>	 GuiFactory::CreateLabels(const std::string& aType)
{
	rapidjson::Document document;
	ParseDocument(document);

	std::vector<std::unique_ptr<Label>> labels;

	auto interfaceObject = document[aType.c_str()].GetObject();
	for (auto& labelObj : interfaceObject["texts"].GetArray())
	{
		auto& font = m_sharedContext->m_fonts.GetResource(labelObj["font"].GetString());
		auto label = std::make_unique<Label>(m_sharedContext->m_window, labelObj["string"].GetString(), font, labelObj["font_size"].GetInt());

		label->SetPosition({ labelObj["position"]["x"].GetFloat(), labelObj["position"]["y"].GetFloat() });
		label->SetRotation(labelObj["rotation"].GetFloat());
		label->SetStyle(labelObj["style"].GetInt());

		auto color = labelObj["color"].GetObject();
		label->SetFillColor({ (sf::Uint8)color["red"].GetInt(), (sf::Uint8)color["green"].GetInt(), (sf::Uint8)color["blue"].GetInt(), (sf::Uint8)color["alpha"].GetInt() });

		color = labelObj["border_color"].GetObject();
		label->SetBorderColor({ (sf::Uint8)color["red"].GetInt(), (sf::Uint8)color["green"].GetInt(), (sf::Uint8)color["blue"].GetInt(), (sf::Uint8)color["alpha"].GetInt() });
		label->SetBorderThickness(labelObj["border_thickness"].GetFloat());

		labels.push_back(std::move(label));
	}
	return labels;
}

std::vector<std::unique_ptr<Button>> GuiFactory::CreateButtons(const std::string& aType)
{
	rapidjson::Document document;
	ParseDocument(document);

	std::vector<std::unique_ptr<Button>> buttons;
	
	auto interfaceObject = document[aType.c_str()].GetObject();
	for (auto& buttonObj : interfaceObject["buttons"].GetArray())
	{
		auto& font = m_sharedContext->m_fonts.GetResource(buttonObj["font"].GetString());
		auto button = std::make_unique<Button>(m_sharedContext->m_window, buttonObj["string"].GetString(), font, buttonObj["font_size"].GetInt());

		button->SetPosition({ buttonObj["position"]["x"].GetFloat(), buttonObj["position"]["y"].GetFloat() });
		button->SetSize({ buttonObj["size"]["width"].GetFloat(), buttonObj["size"]["height"].GetFloat() });
		button->SetBorderThickness(buttonObj["border_thickness"].GetFloat());
		button->SetAction(buttonObj["action"].GetInt());

		auto color = buttonObj["background_color"].GetObject();
		button->SetContainerColor({ (sf::Uint8)color["red"].GetInt(), (sf::Uint8)color["green"].GetInt(), (sf::Uint8)color["blue"].GetInt(), (sf::Uint8)color["alpha"].GetInt() });
		color = buttonObj["text_color"].GetObject();
		button->SetTextColor({ (sf::Uint8)color["red"].GetInt(), (sf::Uint8)color["green"].GetInt(), (sf::Uint8)color["blue"].GetInt(), (sf::Uint8)color["alpha"].GetInt() });
		color = buttonObj["border_color"].GetObject();
		button->SetBorderColor({ (sf::Uint8)color["red"].GetInt(), (sf::Uint8)color["green"].GetInt(), (sf::Uint8)color["blue"].GetInt(), (sf::Uint8)color["alpha"].GetInt() });
		button->Center();

		buttons.push_back(std::move(button));
	}
	return buttons;
}

void GuiFactory::SetContext(const SharedContext* aSharedContext)
{
	m_sharedContext = aSharedContext;
}

void GuiFactory::ParseDocument(rapidjson::Document& aDocument)
{
	std::ifstream ifs{ "Assets/Json/Interfaces.json" };
	std::string	  content{ std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) };

	if (aDocument.Parse(content.c_str()).HasParseError())
	{
		std::cerr << "[GuiFactory] Error parsing \'Interfaces.json\'!\n";
		return;
	}
}