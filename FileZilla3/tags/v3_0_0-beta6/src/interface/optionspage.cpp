#include "FileZilla.h"
#include "Options.h"
#include "settingsdialog.h"
#include "optionspage.h"

wxString validationFailed = _("Failed to validate settings");

bool COptionsPage::CreatePage(COptions* pOptions, CSettingsDialog* pOwner, wxWindow* parent, wxSize& maxSize)
{
	m_pOwner = pOwner;
	m_pOptions = pOptions;

	if (!wxXmlResource::Get()->LoadPanel(this, parent, GetResourceName()))
		return false;

	wxSize size = GetSize();
	if (size.GetWidth() > maxSize.GetWidth())
		maxSize.SetWidth(size.GetWidth());
	if (size.GetHeight() > maxSize.GetHeight())
		maxSize.SetHeight(size.GetHeight());

	return true;
}

void COptionsPage::SetCheck(int id, bool checked, bool& failure)
{
	wxCheckBox* pCheckBox = wxDynamicCast(FindWindow(id), wxCheckBox);
	if (!pCheckBox)
	{
		failure = true;
		return;
	}

	pCheckBox->SetValue(checked);
}

bool COptionsPage::GetCheck(int id)
{
	wxCheckBox* pCheckBox = wxDynamicCast(FindWindow(id), wxCheckBox);
	wxASSERT(pCheckBox);

	return pCheckBox->GetValue();
}

void COptionsPage::SetTextFromOption(int ctrlId, int optionId, bool& failure)
{
	wxTextCtrl* pTextCtrl = wxDynamicCast(FindWindow(ctrlId), wxTextCtrl);
	if (!pTextCtrl)
	{
		failure = true;
		return;
	}

	const wxString& text = m_pOptions->GetOption(optionId);
	pTextCtrl->SetValue(text);
}

wxString COptionsPage::GetText(int id)
{
	wxTextCtrl* pTextCtrl = wxDynamicCast(FindWindow(id), wxTextCtrl);
	wxASSERT(pTextCtrl);

	return pTextCtrl->GetValue();
}

void COptionsPage::SetRCheck(int id, bool checked, bool& failure)
{
	wxRadioButton* pRadioButton = wxDynamicCast(FindWindow(id), wxRadioButton);
	if (!pRadioButton)
	{
		failure = true;
		return;
	}

	pRadioButton->SetValue(checked);
}

bool COptionsPage::GetRCheck(int id)
{
	wxRadioButton* pRadioButton = wxDynamicCast(FindWindow(id), wxRadioButton);
	wxASSERT(pRadioButton);

	return pRadioButton->GetValue();
}

void COptionsPage::SetStaticText(int id, const wxString& text, bool& failure)
{
	wxStaticText* pStaticText = wxDynamicCast(FindWindow(id), wxStaticText);
	if (!pStaticText)
	{
		failure = true;
		return;
	}

	pStaticText->SetLabel(text);
}

wxString COptionsPage::GetStaticText(int id)
{
	wxStaticText* pStaticText = wxDynamicCast(FindWindow(id), wxStaticText);
	wxASSERT(pStaticText);

	return pStaticText->GetLabel();
}

void COptionsPage::ReloadSettings()
{
	m_pOwner->LoadSettings();
}

void COptionsPage::SetOptionFromText(int ctrlId, int optionId)
{
	const wxString& value = GetText(ctrlId);
	m_pOptions->SetOption(optionId, value);
}
