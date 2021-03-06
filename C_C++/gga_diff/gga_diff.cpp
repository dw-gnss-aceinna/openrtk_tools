// gga_diff.cpp : Defines the entry point for the console application.
//


#include "nemagga.h"

using namespace gnssimu_lib;

#define APPLY_LA

void print_kml_heder(FILE* fKML)
{
	// write header for KML 
	if (fKML) {
		fprintf(fKML, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		fprintf(fKML, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
		fprintf(fKML, "<Document>\n");
		// fprintf(fKML, "<Placemark>\n");    
		// fprintf(fKML, "<name>extruded</name>\n");
		// fprintf(fKML, "<LineString>\n");
		// fprintf(fKML, "<extrude>1</extrude>\n");
		// fprintf(fKML, "<tessellate>1</tessellate>\n");
		// fprintf(fKML, "<altitudeMode>relativeToGround</altitudeMode>\n");
		// fprintf(fKML, "<coordinates>\n"); 
		fprintf(fKML, "<Style id=\"solu1\">\n");
		fprintf(fKML, "<IconStyle>\n");
		fprintf(fKML, "<color>ffff00ff</color>\n");
		fprintf(fKML, "<scale>0.300</scale>\n");
		fprintf(fKML, "<Icon>\n");
		fprintf(fKML, "<href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png</href>\n");
		fprintf(fKML, "</Icon>\n");
		fprintf(fKML, "</IconStyle>\n");
		fprintf(fKML, "</Style>\n");
		fprintf(fKML, "<Style id=\"solu11\">\n");
		fprintf(fKML, "<IconStyle>\n");
		fprintf(fKML, "<color>ffff00ff</color>\n");
		fprintf(fKML, "<scale>0.500</scale>\n");
		fprintf(fKML, "<Icon>\n");
		fprintf(fKML, "<href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png</href>\n");
		fprintf(fKML, "</Icon>\n");
		fprintf(fKML, "</IconStyle>\n");
		fprintf(fKML, "</Style>\n");
		fprintf(fKML, "<Style id=\"solu4\">\n");
		fprintf(fKML, "<IconStyle>\n");
		fprintf(fKML, "<color>ff008800</color>\n");
		fprintf(fKML, "<scale>0.300</scale>\n");
		fprintf(fKML, "<Icon>\n");
		fprintf(fKML, "<href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png</href>\n");
		fprintf(fKML, "</Icon>\n");
		fprintf(fKML, "</IconStyle>\n");
		fprintf(fKML, "</Style>\n");
		fprintf(fKML, "<Style id=\"solu5\">\n");
		fprintf(fKML, "<IconStyle>\n");
		fprintf(fKML, "<color>ff00aaff</color>\n");
		fprintf(fKML, "<scale>0.300</scale>\n");
		fprintf(fKML, "<Icon>\n");
		fprintf(fKML, "<href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png</href>\n");
		fprintf(fKML, "</Icon>\n");
		fprintf(fKML, "</IconStyle>\n");
		fprintf(fKML, "</Style>\n");
		fprintf(fKML, "<Style id=\"solu15\">\n");
		fprintf(fKML, "<IconStyle>\n");
		fprintf(fKML, "<color>ff00aaff</color>\n");
		fprintf(fKML, "<scale>0.500</scale>\n");
		fprintf(fKML, "<Icon>\n");
		fprintf(fKML, "<href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle.png</href>\n");
		fprintf(fKML, "</Icon>\n");
		fprintf(fKML, "</IconStyle>\n");
		fprintf(fKML, "</Style>\n");
	}
	return;
}

void print_kml_gga(FILE* fKML, double lat, double lon, double ht, int type)
{
	if (fKML == NULL) return;
	if (fKML) {
		fprintf(fKML, "<Placemark>\n");
		if (type == 1)
		{
			fprintf(fKML, "<styleUrl>#solu1</styleUrl>\n");
		}
		else if (type == 4)
		{
			fprintf(fKML, "<styleUrl>#solu4</styleUrl>\n");
		}
		else if (type == 5)
		{
			fprintf(fKML, "<styleUrl>#solu5</styleUrl>\n");
		}
		else if (type == 11)
		{
			fprintf(fKML, "<styleUrl>#solu11</styleUrl>\n");
		}
		else if (type == 15)
		{
			fprintf(fKML, "<styleUrl>#solu15</styleUrl>\n");
		}
		else
		{
			fprintf(fKML, "<styleUrl>#solu1</styleUrl>\n");
		}
		//fprintf(fKML, "<ExtendedData>\n");
		//fprintf(fKML, "<Data name=\"time\">\n");
		//fprintf(fKML, "<value>%.3lf</value>\n", gga.time);
		//fprintf(fKML, "</Data>\n");
		//fprintf(fKML, "</ExtendedData>\n");
		fprintf(fKML, "<Point>\n");
		fprintf(fKML, "<coordinates>%14.9f,%14.9f,%14.4f</coordinates>\n", lon, lat, ht);
		fprintf(fKML, "</Point>\n");
		fprintf(fKML, "</Placemark>\n");
	}
	return;
}

void print_kml_eof(FILE* fKML)
{
	if (fKML)
	{
		// fprintf(fKML, "</coordinates>\n");    
		// fprintf(fKML, "</LineString>\n");
		// fprintf(fKML, "</Placemark>\n");
		fprintf(fKML, "</Document>\n");
		fprintf(fKML, "</kml>\n");

	}
}


void	att2C_nb(double* att, double C_nb[3][3])
{
	// attitude: roll, pitch and heading
	// attitude => C_nb
	double R = att[0], P = att[1], H = att[2];
	C_nb[0][0] = cos(H) * cos(P);
	C_nb[1][0] = sin(H) * cos(P);
	C_nb[2][0] = -sin(P);
	C_nb[0][1] = -sin(H) * cos(R) + cos(H) * sin(P) * sin(R);
	C_nb[1][1] = cos(H) * cos(R) + sin(H) * sin(P) * sin(R);
	C_nb[2][1] = cos(P) * sin(R);
	C_nb[0][2] = sin(H) * sin(R) + cos(H) * sin(P) * cos(R);
	C_nb[1][2] = -cos(H) * sin(R) + sin(H) * sin(P) * cos(R);
	C_nb[2][2] = cos(P) * cos(R);
	return;
}

void rotate_vector1(double C[3][3], double* vec, double *vec_out, int isTranspose)
{
	if (isTranspose == 0)
	{
		vec_out[0] = C[0][0] * vec[0] + C[0][1] * vec[1] + C[0][2] * vec[2];
		vec_out[1] = C[1][0] * vec[0] + C[1][1] * vec[1] + C[1][2] * vec[2];
		vec_out[2] = C[2][0] * vec[0] + C[2][1] * vec[1] + C[2][2] * vec[2];
	}
	else
	{
		vec_out[0] = C[0][0] * vec[0] + C[1][0] * vec[1] + C[2][0] * vec[2];
		vec_out[1] = C[0][1] * vec[0] + C[1][1] * vec[1] + C[2][1] * vec[2];
		vec_out[2] = C[0][2] * vec[0] + C[1][2] * vec[1] + C[2][2] * vec[2];
	}
	return;
}

void rotate_vector(double C[3][3], double* vec, int isTranspose)
{
	double temp[3] = { 0.0 };
	rotate_vector1(C, vec, temp, isTranspose);
	vec[0] = temp[0];
	vec[1] = temp[1];
	vec[2] = temp[2];
	return;
}


typedef struct
{
	int wn;
	double ws;
	double rpy[3]; /* Roll, Pitch and Yaw/Heading */
	double vxyz[3];
	double vENU[3];
	double wxyz[3];
	double fxyz[3];
	double xyz[3];
	double rmsRPY[3];
	double rmsENU[3];
	double rmsVenu[3];
	double blh[3];
	int ns;
	double hdop;
}solu1_t;

typedef struct
{
	int wn;
	double ws;
	double blh[3];
	double hdop;
	double pdop;
	int ns;
	double rmsENU[3];
	int type;
}solu2_t;

unsigned long solu_diff(const char* fname1, const char* fname2, int type, double *lao, double stime, double etime)
{
	/* compare the soltion from NovAtel SPAN solution and NMEA GGA */
#if 0
	/* NMEA GGA */
	Week, GPSTime, Roll, Pitch, Heading, VX - ECEF, VY - ECEF, VZ - ECEF, VEast, VNorth, VUp, AngRateX, AngRateY, AngRateZ, AccBdyX, AccBdyY, AccBdyZ, X - ECEF, Y - ECEF, Z - ECEF, RollSD, PitchSD, HdngSD, SDEast, SDNorth, SDHeight, SD - VE, SD - VN, SD - VH, Latitude, Longitude, H - Ell, NS, HDOP
	(weeks, (sec), (deg), (deg), (deg), (m / s), (m / s), (m / s), (m / s), (m / s), (m / s), (deg / s), (deg / s), (deg / s), (m / s ^ 2), (m / s ^ 2), (m / s ^ 2), (m), (m), (m), (deg), (deg), (deg), (m), (m), (m), (m / s), (m / s), (m / s), (deg), (deg), (m), , (dop)
		2069, 423470, 0.391943239, 2.563304313, 60.98594284, 0, 0, 0, 0, 0, 0, 0.0041, -0.0044, 0.0023, 0.023, -0.038, -0.023, -2687728.289, -4281324.497, 3876272.875, 0.007077488, 0.007051909, 0.010994121, 0.011, 0.011, 0.021, 0.003, 0.003, 0.003, 37.66736958, -122.1197648, -19.819, 7, 1.4
#endif
	FILE * fSOL[4] = { NULL };
	char buffer[1024] = { 0 }, outfname[255] = { 0 }, kmlfname[255] = { 0 };
	fSOL[0] = fopen(fname1, "r");
	fSOL[1] = fopen(fname2, "r");

	memcpy(buffer, fname1, strlen(fname1));

	char* result1 = strrchr(buffer, '.');
	if (result1 != NULL) result1[0] = '\0';

	sprintf(outfname, "%s_diff_%06i_%06i.txt", buffer, (int)stime, (int)etime);
	sprintf(kmlfname, "%s_diff_%06i_%06i.kml", buffer, (int)stime, (int)etime);
	fSOL[2] = fopen(outfname, "w");
	fSOL[3] = fopen(kmlfname, "w");

	print_kml_heder(fSOL[3]);

	if (fSOL[0] == NULL || fSOL[1] == NULL)
	{
		if (fSOL[0] != NULL) fclose(fSOL[0]);
		if (fSOL[1] != NULL) fclose(fSOL[1]);
		return 0;
	}
	/* skip two lines */
	fgets(buffer, sizeof(buffer), fSOL[1]);
	fgets(buffer, sizeof(buffer), fSOL[1]);
	solu1_t sol[2] = { 0 };
	solu2_t sol2 = { 0 };
	double xyz_offset[] = {0.0, 0.0, 0.0};
	unsigned long numofepoch = 0;
	double preTime = 0.0;
	double ref_delay_start = -1.0;

	while (!feof(fSOL[0]))
	{
		memset(&sol2, 0, sizeof(sol2));
		fgets(buffer, sizeof(buffer), fSOL[0]);
		if (sscanf(buffer, "%i,%lf,%lf,%lf,%lf,%lf,%lf,%i,%lf,%lf,%lf,%i"
			, &sol2.wn, &sol2.ws
			, sol2.blh + 0, sol2.blh + 1, sol2.blh + 2
			, &sol2.hdop, &sol2.pdop
			, &sol2.ns
			, sol2.rmsENU + 0, sol2.rmsENU + 1, sol2.rmsENU + 2
			, &sol2.type) < 12)
		{
			continue;
		}

		sol2.ws /= 1000.0;
		/*if (sol2.ws - floor(sol2.ws) > 0.09) {
			continue;
		}*/

		sol2.blh[0] *= PI / 180.0;
		sol2.blh[1] *= PI / 180.0;
		if (stime > 0.0 && sol2.ws < stime) continue;
		if (etime > 0.0 && sol2.ws > etime) continue;

		if (ref_delay_start > 0.0) {
			if (sol2.ws < ref_delay_start) {
				continue;
			}
		}

		while (!feof(fSOL[1]))
		{
			if (sol[0].ws <= sol2.ws && sol[1].ws >= sol2.ws)
			{
				/* compare the solution */
				int ii = 0;
				if (ref_delay_start < 0.0) {
					ref_delay_start = sol[1].ws;
				}
				break; 
			}
			solu1_t sol1 = { 0 };
			fgets(buffer, sizeof(buffer), fSOL[1]);
			if (sscanf(buffer, "%i,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%i,%lf"
				, &sol1.wn, &sol1.ws
				, sol1.rpy + 0, sol1.rpy + 1, sol1.rpy + 2
				, sol1.vxyz + 0, sol1.vxyz + 1, sol1.vxyz + 2
				, sol1.vENU + 0, sol1.vENU + 1, sol1.vENU + 2
				, sol1.wxyz + 0, sol1.wxyz + 1, sol1.wxyz + 2
				, sol1.fxyz + 0, sol1.fxyz + 1, sol1.fxyz + 2
				, sol1.xyz + 0, sol1.xyz + 1, sol1.xyz + 2
				, sol1.rmsRPY + 0, sol1.rmsRPY + 1, sol1.rmsRPY + 2
				, sol1.rmsENU + 0, sol1.rmsENU + 1, sol1.rmsENU + 2
				, sol1.rmsVenu + 0, sol1.rmsVenu + 1, sol1.rmsVenu + 2
				, sol1.blh + 0, sol1.blh + 1, sol1.blh + 2
				, &sol1.ns, &sol1.hdop) < 34)
			{
				continue;
			}
			sol1.blh[0] *= PI / 180.0;
			sol1.blh[1] *= PI / 180.0;
			sol[0] = sol[1];
			sol[1] = sol1;

			
		}

		if (sol[0].ws == 0.0 && sol[1].ws >= sol2.ws)
		{
			printf("no overlap start at %10.3f\n", sol2.ws);
			
			//break;
			continue;
		}

		if (sol[0].ws <= sol2.ws && sol[1].ws >= sol2.ws)
		{
			/* interpolate */
			double dt1 = sol2.ws - sol[0].ws;
			double dt2 = sol2.ws - sol[1].ws;
			double dt = 0.0;
			double xyz_ref[3] = { 0 };
			double vxyz_ref[3] = { 0 };
			double att_ref[3] = { 0 };
			if (fabs(dt1) > fabs(dt2))
			{
				for (int i = 0; i < 3; ++i)
				{
					xyz_ref[i] = sol[1].xyz[i];
					vxyz_ref[i] = sol[1].vxyz[i];
					att_ref[i] = sol[1].rpy[i] * PI / 180.0;
				}
				dt = dt2;
			}
			else
			{
				for (int i = 0; i < 3; ++i)
				{
					xyz_ref[i] = sol[0].xyz[i];
					vxyz_ref[i] = sol[0].vxyz[i];
					att_ref[i] = sol[0].rpy[i] * PI / 180.0;
				}
				dt = dt1;
			}

			double xyz_[3] = { 0.0 };
			double blh_[3] = { 0 };
			double C_en[3][3] = { 0 };
			for (int i = 0; i < 3; ++i) {
				xyz_[i] = xyz_ref[i] + vxyz_ref[i] * dt + xyz_offset[i];
			}

			xyz2blh(xyz_, blh_);
			blh2C_en(blh_, C_en);
			double xyz[3] = { 0.0 };
			double blh[3] = { sol2.blh[0], sol2.blh[1], sol2.blh[2] };
			blh2xyz(blh, xyz);
			double C_nb[3][3] = { 0 };
			att2C_nb(att_ref, C_nb);
			double dned[3] = { 0.0 };

			double lao_b[3] = { 0.0 };
#ifdef APPLY_LA
			double lao_n[3] = { 0.0 };
			double lao_e[3] = { 0.0 };
			if (lao != NULL)
			{
				lao_b[0] = lao[0];
				lao_b[1] = lao[1];
				lao_b[2] = lao[2];
			}
			rotate_vector1(C_nb, lao_b, lao_n, 0);
			rotate_vector1(C_en, lao_n, lao_e, 0);
			xyz[0] += lao_e[0];
			xyz[1] += lao_e[1];
			xyz[2] += lao_e[2];
			xyz2blh(xyz, blh);

#endif
			double dxyz[3] = { xyz[0] - xyz_[0], xyz[1] - xyz_[1], xyz[2] - xyz_[2] };
			rotate_vector1(C_en, dxyz, dned, 1); /* xyz => ned */
#ifndef APPLY_LA
			rotate_vector1(C_nb, dned, lao_b, 1);
#endif

			double diffH = sqrt(dned[0] * dned[0] + dned[1] * dned[1]);
			double diff3 = sqrt(dned[0] * dned[0] + dned[1] * dned[1] + dned[2] * dned[2]);

			fprintf(fSOL[2], "%10.3f,%14.9f,%14.9f,%10.4f,%10.4f,%10.4f,%10.4f,%10.4f,%10.4f,%02i,%02i,%7.3f,%7.3f,%7.3f,%10.4f,%10.4f,%10.4f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n"
				, sol2.ws, sol2.blh[0] * 180.0 / PI, sol2.blh[1] * 180.0 / PI, sol2.blh[2]
				, dned[0], dned[1], dned[2], diffH, diff3, sol2.ns, sol2.type, sol2.rmsENU[0], sol2.rmsENU[1], sol2.rmsENU[2], att_ref[0], att_ref[1], att_ref[2],
				vxyz_ref[0], vxyz_ref[1], vxyz_ref[2], lao_b[0], lao_b[1], lao_b[2]
				);

			if (floor(sol2.ws + 0.5) != floor(preTime + 0.5))
			{
				print_kml_gga(fSOL[3], sol2.blh[0] * 180.0 / PI, sol2.blh[1] * 180.0 / PI, sol2.blh[2], type);
				//print_kml_gga(fSOL[3], blh[0] * 180.0 / PI, blh[1] * 180.0 / PI, blh[2], type+10);
				print_kml_gga(fSOL[3], blh_[0] * 180.0 / PI, blh_[1] * 180.0 / PI, blh_[2], 4);
			}

			++numofepoch;
		}
		preTime = sol2.ws;
		int jj = 0;
	}

	print_kml_eof(fSOL[3]);
	if (fSOL[0] != NULL) fclose(fSOL[0]);
	if (fSOL[1] != NULL) fclose(fSOL[1]);
	if (fSOL[2] != NULL) fclose(fSOL[2]);
	if (fSOL[3] != NULL) fclose(fSOL[3]);

	return numofepoch;
}


int main(int argc, char* argv[])
{
	double lao[3] = { 0.43, 0.91, 1.33 }; //{ 0.0 };//
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_spp\\f9_190905_181418_DC-SF.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_spp\\f9_190905_210831_Oakland-Hayward.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 1, lao, 421450.0, 422610.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_spp\\f9_190905_181418_DC-SF.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 1, lao, 0.0, 0.0);

	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\f9_190905_181418_DC-SF_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\f9_190905_210831_Oakland-Hayward_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\f9_190905_181418_DC-SF_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_spp\\m8_008385_2019-09-05T22-20-09.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_rtklib\\m8_rtklib_combined_cc.pos", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_spp\\m8_008383_2019-09-05T20-49-50.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 421450.0, 422610.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_spp\\m8_008382_2019-09-05T20-00-31.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 419040.0, 420600.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_rtklib\\m8_008381_2019-09-05T19-14-37.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_rtklib\\m8_008380_2019-09-05T18-28-32.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_rtklib\\m8_008379_2019-09-05T17-41-08.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);

	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008385_2019-09-05T22-20-09_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao,0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008384_2019-09-05T21-35-09_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008383_2019-09-05T20-49-50_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008382_2019-09-05T20-00-31_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008381_2019-09-05T19-14-37_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008380_2019-09-05T18-28-32_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\248_openRTK\\m8_008379_2019-09-05T17-41-08_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	
	//solu_diff("C:\\Users\\da\\Documents\\248\\outlier_detection\\m8_008385_2019-09-05T22-20-09-test1.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\test2\\m8_008384_2019-09-05T21-35-09-test2.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\outlier_detection\\m8_008383_2019-09-05T20-49-50-test1.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\outlier_detection\\m8_008382_2019-09-05T20-00-31-test1.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\3\\rtk_gg_tesla.pos.stat", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\test2\\m8_008380_2019-09-05T18-28-32-test2.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	solu_diff("C:\\Users\\da\\Documents\\248\\mrtklib\\rtk_gg_381.pos.stat", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);

	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\m8_008385_2019-09-05T22-20-09.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\m8_008384_2019-09-05T21-35-09.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\m8_008383_2019-09-05T20-49-50.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\m8_008382_2019-09-05T20-00-31.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\m8_008381_2019-09-05T19-14-37.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\m8_008380_2019-09-05T18-28-32.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_rtklib\\rtk_gg_com_sf03.pos.stat", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);

	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openRTK\\m8_008385_2019-09-05T22-20-09_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao,0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openRTK\\m8_008384_2019-09-05T21-35-09_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_22-35-53.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openRTK\\m8_008383_2019-09-05T20-49-50_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openRTK\\m8_008382_2019-09-05T20-00-31_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openrtk\\m8_008381_2019-09-05T19-14-37_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openRTK\\m8_008380_2019-09-05T18-28-32_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
	//solu_diff("C:\\Users\\da\\Documents\\248\\OneDrive_1_9-26-2019\\248_openRTK\\m8_008379_2019-09-05T17-41-08_sat.csv", "C:\\Users\\da\\Documents\\248\\reference\\NMPL18520008S_2019-09-05_21-26-45.csv", 5, lao, 0.0, 0.0);
#if 0
	gnssimu_lib::TNEMAGGAReader gga;
	if (argc >= 1)
		gga.ReadPOS(argv[1]);// "C:\\rtklib\\process\\qxwz\\82101250.pos");
#if 0
							 //if (argc < 4)
							 //		return;
							 //gnssimu_lib::gga_diff(argv[1], argv[2], argv[3]);
#else
							 //gnssimu_lib::gga_diff("D:\\RTK20170713\\Projects\\Prj_RTKOffLine\\rtkpost.sol", "D:\\RTK20170713\\0524_fix\\rtkpost.sol", "aa.txt");
	gnssimu_lib::gga_diff("D:\\share\\20170614\\BX306_05.nmea", "D:\\share\\20170614\\PP\\rtkpost.sol", "D:\\share\\20170614\\aa.csv");
#endif
#endif
	return 0;
}
