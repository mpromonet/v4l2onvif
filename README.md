# v4l2-onvif

   It implements an ONVIF server :
   
   * for V4L2 capture devices (NVT/NVS),
   * for V4L2 output devices (NVD).
   
   The web services data binding is generated using [gSOAP](http://www.genivia.com/).

## License

   [GNU General Public License](http://www.gnu.org/licenses/#GPL)

## Build

    make ; make

## Usage

    server.exe [-u username] [-p password] [-i v4l2 input device] [-I rtsp server] [-o v4l2 output device] [-O rtsp client]
