#include <stdexcept>
void ParticleImage::Write3dout(std::ofstream &file, double x, double y, double z)
{
    if (file.good()) {
        string line;
        real val = 0.0;

        // vector of arrays to store primary coordinates.  First
        // 3 values are the cartesian coordinates, final value
        // is the primary radius.
        vector<fvector> coords;

        // Get the primary coordinates from the aggregate tree.
        m_root.GetPriCoords(coords);
		file.write(line.c_str(), line.length());
        //write the radius of gyration
        double Rg=RadiusofGyration();
        line = cstr(0) + " " + cstr(0) +
               " " + cstr(0)+"\n ";
        file.write(line.c_str(), line.length());
        line = cstr(Rg)+"\n";							//write radius of gyration
        file.write(line.c_str(), line.length());
        // Write the primaries to the 3dout file.
        for (unsigned int i=0; i!=coords.size(); ++i) {
            val  = coords[i][3] * m_necking;
            line = cstr(coords[i][0]+x) + " " + cstr(coords[i][1]+y) +
                   " " + cstr(coords[i][2]+z)+"\n ";
            file.write(line.c_str(), line.length());
            line = cstr(val)+"\n";							//write radius
            file.write(line.c_str(), line.length());
        }


    } else {
        throw invalid_argument("Output stream not ready "
                               "(Sweep, ParticleImage::Write3dout).");
    }
}
