//
// MainPage.xaml.h
// Déclaration de la classe MainPage.
//

#pragma once

#include "MainPage.g.h"

namespace ChronoTELECOM
{
	/// <summary>
	/// Une page vide peut être utilisée seule ou constituer une page de destination au sein d'un frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void cmd_chronometre_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void txb_temps_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void cmd_pause_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void cmd_reset_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void getLL_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void listView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
	};
}
