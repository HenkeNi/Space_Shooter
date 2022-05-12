#pragma once
#include "SharedContext.h"

class Image; 
class Widget; 
class Label; 
class Button;


class GuiFactory
{
public:
	GuiFactory(const GuiFactory&)				= delete;
	GuiFactory& operator=(const GuiFactory&)	= delete;	

	static GuiFactory&						GetInstance();

	std::vector<std::unique_ptr<Image>>		CreateImages(const std::string& aType);
	std::vector<std::unique_ptr<Label>>		CreateLabels(const std::string& aType);
	std::vector<std::unique_ptr<Button>>	CreateButtons(const std::string& aType);
	void									SetContext(const SharedContext* aSharedContext);

private:
	GuiFactory();
	void									ParseDocument(rapidjson::Document& aDocument);

	const SharedContext*					m_sharedContext;
};

