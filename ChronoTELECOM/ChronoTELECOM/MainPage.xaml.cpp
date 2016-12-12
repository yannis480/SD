//
// MainPage.xaml.cpp
// Implémentation de la classe MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <thread>
#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <ctime>




using namespace ChronoTELECOM;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Devices::Geolocation;
using namespace concurrency;

typedef struct instant
{
	int secondes;
	int minutes;
	int heures;
	double latitude;
	double longitude;


} instant;


// Pour en savoir plus sur le modèle d'élément Page vierge, consultez la page http://go.microsoft.com/fwlink/?LinkId=234238
int secondes = 00;
int minutes = 00;
int heures = 00;
double Get_GlobalLatitude;
double Get_GlobalLongitude;

std::list<instant> Parcours;


std::string etat;
std::chrono::time_point<std::chrono::system_clock> start, end;

void fct_threadGPS(void)
{
	//Cette fonction s'occupe de la gestion du GPS
	Geolocator GeoLoc;
	Windows::Devices::Geolocation::Geolocator^ geolocator;
	geolocator = ref new Geolocator();


	while (1)
	{
		task<Geoposition^> geopositionTask(geolocator->GetGeopositionAsync()); //On recupere la position de maniere Asyncrone
		{
			Geoposition^ pos = geopositionTask.get();
			Get_GlobalLatitude = pos->Coordinate->Point->Position.Latitude;
			Get_GlobalLongitude = pos->Coordinate->Point->Position.Longitude;

		}
	}
}



MainPage::MainPage()
{
	InitializeComponent();
	std::thread threadGps(fct_threadGPS);
	//std::thread ThreadChrono(fct_threadChrono);
	threadGps.detach();
	//ThreadChrono.detach();
}

/// <summary>
/// Invoqué lorsque cette page est sur le point d'être affichée dans un frame.
/// </summary>
/// <param name="e">Données d'événement décrivant la manière dont l'utilisateur a accédé à cette page.  La propriété Parameter
/// est généralement utilisée pour configurer la page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Paramètre non utilisé

	// TODO: préparer la page pour affichage ici.

	// TODO: si votre application comporte plusieurs pages, assurez-vous que vous
	// gérez le bouton Retour physique en vous inscrivant à l’événement
	// Événement Windows::Phone::UI::Input::HardwareButtons.BackPressed.
	// Si vous utilisez le NavigationHelper fourni par certains modèles,
	// cet événement est géré automatiquement.
}


void chronometre()
{
	//ajout d'une seconde
	Sleep(1000);
	 

		secondes = secondes + 1;
		if (secondes == 60)
		{
			//On incremente une minutes lorsqu'on a 60 secondes
			minutes = minutes + 1;
			secondes = 0;
			if (minutes == 60)
			{
				//On incremente les heures lorsqu'on a 60 minutes
				heures = minutes + 1;
				minutes = 0;
			}
		}
	
}

void ChronoTELECOM::MainPage::cmd_chronometre_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	etat =  "marche";
	//Creation d'un nouveau thread , execution de ce thread , ne block pas l'execution
	std::thread t1(chronometre);
	//Fait un wait pour le nouveau thread pour arreter l'exection
	t1.join();
	txb_temps->Text = heures.ToString() + ":" + minutes.ToString() + ":" + secondes.ToString() ;
}
 

void ChronoTELECOM::MainPage::txb_temps_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{

		if (etat.compare("marche")==0)
		{
			cmd_chronometre_Click(sender, e);

		}


		if (etat.compare("pause")==0)
		{
			txb_temps->Text = heures.ToString() + ":" + minutes.ToString() + ":" + secondes.ToString() ;

		}

		if (etat.compare("reset") == 0)
		{
			heures = 00; minutes = 00; secondes = 00;
			txb_temps->Text = heures.ToString() + " : " + minutes.ToString() + " : " + secondes.ToString() ;
		}
   
}


void ChronoTELECOM::MainPage::cmd_pause_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	etat = "pause";	
	txb_temps->Text = heures.ToString() + ":" + minutes.ToString() + ":" + secondes.ToString() ;
	instant t1;
	t1.secondes = secondes;
	t1.minutes = minutes;
	t1.heures = heures;
	t1.longitude = Get_GlobalLongitude;
	t1.latitude = Get_GlobalLatitude;
	lati->Text = Get_GlobalLatitude.ToString();
	longitude->Text = Get_GlobalLongitude.ToString();
	Parcours.push_back(t1);
}

void ChronoTELECOM::MainPage::cmd_reset_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	etat = "reset";
	instant t1;
	t1.secondes = secondes;
	t1.minutes = minutes;
	t1.heures = heures;
	t1.longitude = Get_GlobalLongitude;
	t1.latitude = Get_GlobalLatitude;
	Parcours.push_back(t1);
	heures = 00; minutes = 00; secondes = 00;
	txb_temps->Text = heures.ToString() + " : " + minutes.ToString() + " : " + secondes.ToString() ;
	lati->Text = Get_GlobalLatitude.ToString();
	longitude->Text = Get_GlobalLongitude.ToString();
	historique->Text = historique->Text+ "Temps :"+t1.heures.ToString() + " : " + t1.minutes.ToString() + " : " + t1.secondes.ToString()+"  coordonées : "+t1.longitude+"  "+t1.latitude+"\r\n";
}



void ChronoTELECOM::MainPage::getLL_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	lati->Text = Get_GlobalLatitude.ToString();
	longitude->Text = Get_GlobalLongitude.ToString();
}


