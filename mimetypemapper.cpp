#include "mimetypemapper.h"

MimeTypeMapper::MimeTypeMapper()
{
	insert(".a", "application/octet-stream");
	insert(".abc", "text/vnd.abc");
	insert(".acgi", "text/html");
	insert(".afl", "video/animaflex");
	insert(".ai", "application/postscript");
	insert(".aif", "audio/aiff");
	insert(".aifc", "audio/aiff");
	insert(".aiff", "audio/aiff");
	insert(".aps", "application/mime");
	insert(".arc", "application/octet-stream");
	insert(".arj", "application/octet-stream");
	insert(".asp", "text/asp");
	insert(".au", "audio/basic");
	insert(".avi", "video/msvideo");
	insert(".avs", "video/avs-video");
	insert(".bin", "application/octet-stream");
	insert(".bm", "image/bmp");
	insert(".bmp", "image/bmp");
	insert(".boo", "application/book");
	insert(".book", "application/book");
	insert(".c", "text/plain");
	insert(".c++", "text/plain");
	insert(".cat", "application/vnd.ms-pki.seccat");
	insert(".cc", "text/plain");
	insert(".ccad", "application/clariscad");
	insert(".cdf", "application/cdf");
	insert(".cer", "application/pkix-cert");
	insert(".class", "application/java-byte-code");
	insert(".com", "text/plain");
	insert(".conf", "text/plain");
	insert(".cpt", "application/mac-compactpro");
	insert(".crl", "application/pkix-crl");
	insert(".crt", "application/pkix-cert");
	insert(".css", "text/css");
	insert(".cxx", "text/plain");
	insert(".def", "text/plain");
	insert(".dl", "video/dl");
	insert(".doc", "application/msword");
	insert(".dot", "application/msword");
	insert(".dp", "application/commonground");
	insert(".drw", "application/drafting");
	insert(".dump", "application/octet-stream");
	insert(".dwf", "model/vnd.dwf");
	insert(".dwg", "image/vnd.dwg");
	insert(".dxf", "image/vnd.dwg");
	insert(".eps", "application/postscript");
	insert(".evy", "application/envoy");
	insert(".exe", "application/octet-stream");
	insert(".f", "text/plain");
	insert(".f90", "text/plain");
	insert(".fdf", "application/vnd.fdf");
	insert(".fif", "image/fif");
	insert(".fli", "video/fli");
	insert(".flo", "image/florian");
	insert(".flx", "text/vnd.fmi.flexstor");
	insert(".for", "text/plain");
	insert(".fpx", "image/vnd.net-fpx");
	insert(".frl", "application/freeloader");
	insert(".funk", "audio/make");
	insert(".g", "text/plain");
	insert(".g3", "image/g3fax");
	insert(".gif", "image/gif");
	insert(".gl", "video/gl");
	insert(".h", "text/plain");
	insert(".hgl", "application/vnd.hp-hpgl");
	insert(".hh", "text/plain");
	insert(".hlp", "application/hlp");
	insert(".hpg", "application/vnd.hp-hpgl");
	insert(".hpgl", "application/vnd.hp-hpgl");
	insert(".hqx", "application/mac-binhex40");
	insert(".hta", "application/hta");
	insert(".htm", "text/html");
	insert(".html", "text/html");
	insert(".htmls", "text/html");
	insert(".htt", "text/webviewhtml");
	insert(".htx", "text/html");
	insert(".idc", "text/plain");
	insert(".ief", "image/ief");
	insert(".iefs", "image/ief");
	insert(".iges", "model/iges");
	insert(".igs", "model/iges");
	insert(".inf", "application/inf");
	insert(".it", "audio/it");
	insert(".ivr", "i-world/i-vrml");
	insert(".jav", "text/plain");
	insert(".java", "text/plain");
	insert(".jfif", "image/pjpeg");
	insert(".jfif-tbnl", "image/jpeg");
	insert(".jpe", "image/pjpeg");
	insert(".jpeg", "image/pjpeg");
	insert(".jpg", "image/pjpeg");
	insert(".jut", "image/jutvision");
	insert(".kar", "audio/midi");
	insert(".la", "audio/nspaudio");
	insert(".lha", "application/octet-stream");
	insert(".lhx", "application/octet-stream");
	insert(".list", "text/plain");
	insert(".lma", "audio/nspaudio");
	insert(".log", "text/plain");
	insert(".lst", "text/plain");
	insert(".lzh", "application/octet-stream");
	insert(".lzx", "application/octet-stream");
	insert(".m", "text/plain");
	insert(".m1v", "video/mpeg");
	insert(".m2a", "audio/mpeg");
	insert(".m2v", "video/mpeg");
	insert(".mar", "text/plain");
	insert(".mbd", "application/mbedlet");
	insert(".mcd", "application/mcad");
	insert(".mcf", "text/mcf");
	insert(".mcp", "application/netmc");
	insert(".mht", "message/rfc822");
	insert(".mhtml", "message/rfc822");
	insert(".mid", "music/crescendo");
	insert(".midi", "music/crescendo");
	insert(".mime", "www/mime");
	insert(".mm", "application/base64");
	insert(".mme", "application/base64");
	insert(".mod", "audio/mod");
	insert(".moov", "video/quicktime");
	insert(".mov", "video/quicktime");
	insert(".mp2", "video/mpeg");
	insert(".mp3", "video/mpeg");
	insert(".mpa", "video/mpeg");
	insert(".mpe", "video/mpeg");
	insert(".mpeg", "video/mpeg");
	insert(".mpg", "video/mpeg");
	insert(".mpga", "audio/mpeg");
	insert(".mpp", "application/vnd.ms-project");
	insert(".mrc", "application/marc");
	insert(".my", "audio/make");
	insert(".nap", "image/naplps");
	insert(".naplps", "image/naplps");
	insert(".ncm", "application/vnd.nokia.configuration-message");
	insert(".o", "application/octet-stream");
	insert(".oda", "application/oda");
	insert(".p10", "application/pkcs10");
	insert(".p12", "application/pkcs-12");
	insert(".p7c", "application/pkcs7-mime");
	insert(".p7m", "application/pkcs7-mime");
	insert(".p7s", "application/pkcs7-signature");
	insert(".part", "application/pro_eng");
	insert(".pas", "text/pascal");
	insert(".pcl", "application/vnd.hp-pcl");
	insert(".pdf", "application/pdf");
	insert(".pfunk", "audio/make.my.funk");
	insert(".pic", "image/pict");
	insert(".pict", "image/pict");
	insert(".pko", "application/vnd.ms-pki.pko");
	insert(".pl", "text/plain");
	insert(".png", "image/png");
	insert(".pot", "application/vnd.ms-powerpoint");
	insert(".ppa", "application/vnd.ms-powerpoint");
	insert(".pps", "application/vnd.ms-powerpoint");
	insert(".ppt", "application/vnd.ms-powerpoint");
	insert(".ppz", "application/mspowerpoint");
	insert(".prt", "application/pro_eng");
	insert(".ps", "application/postscript");
	insert(".psd", "application/octet-stream");
	insert(".pwz", "application/vnd.ms-powerpoint");
	insert(".qcp", "audio/vnd.qcelp");
	insert(".qt", "video/quicktime");
	insert(".ras", "image/cmu-raster");
	insert(".rast", "image/cmu-raster");
	insert(".rf", "image/vnd.rn-realflash");
	insert(".rm", "application/vnd.rn-realmedia");
	insert(".rmi", "audio/mid");
	insert(".rng", "application/vnd.nokia.ringing-tone");
	insert(".rnx", "application/vnd.rn-realplayer");
	insert(".rp", "image/vnd.rn-realpix");
	insert(".rt", "text/vnd.rn-realtext");
	insert(".rtf", "text/richtext");
	insert(".rtx", "text/richtext");
	insert(".rv", "video/vnd.rn-realvideo");
	insert(".s3m", "audio/s3m");
	insert(".saveme", "application/octet-stream");
	insert(".sdml", "text/plain");
	insert(".sdp", "application/sdp");
	insert(".sdr", "application/sounder");
	insert(".sea", "application/sea");
	insert(".set", "application/set");
	insert(".sgm", "text/sgml");
	insert(".sgml", "text/sgml");
	insert(".shtml", "text/html");
	insert(".smi", "application/smil");
	insert(".smil", "application/smil");
	insert(".snd", "audio/basic");
	insert(".sol", "application/solids");
	insert(".spl", "application/futuresplash");
	insert(".ssm", "application/streamingmedia");
	insert(".sst", "application/vnd.ms-pki.certstore");
	insert(".step", "application/step");
	insert(".stl", "application/vnd.ms-pki.stl");
	insert(".stp", "application/step");
	insert(".svf", "image/vnd.dwg");
	insert(".tbk", "application/toolbook");
	insert(".text", "text/plain");
	insert(".tgz", "application/gnutar");
	insert(".tif", "image/tiff");
	insert(".tiff", "image/tiff");
	insert(".tsi", "audio/tsp-audio");
	insert(".tsp", "audio/tsplayer");
	insert(".tsv", "text/tab-separated-values");
	insert(".turbot", "image/florian");
	insert(".txt", "text/plain");
	insert(".uni", "text/uri-list");
	insert(".unis", "text/uri-list");
	insert(".unv", "application/i-deas");
	insert(".uri", "text/uri-list");
	insert(".uris", "text/uri-list");
	insert(".uu", "application/octet-stream");
	insert(".vda", "application/vda");
	insert(".vdo", "video/vdo");
	insert(".vew", "application/groupwise");
	insert(".viv", "video/vnd.vivo");
	insert(".vivo", "video/vnd.vivo");
	insert(".vmd", "application/vocaltec-media-desc");
	insert(".vmf", "application/vocaltec-media-file");
	insert(".voc", "audio/voc");
	insert(".vos", "video/vosaic");
	insert(".vox", "audio/voxware");
	insert(".vrml", "model/vrml");
	insert(".w60", "application/wordperfect6.0");
	insert(".w61", "application/wordperfect6.1");
	insert(".w6w", "application/msword");
	insert(".wav", "audio/wav");
	insert(".wbmp", "image/vnd.wap.wbmp");
	insert(".web", "application/vnd.xara");
	insert(".wiz", "application/msword");
	insert(".wmf", "windows/metafile");
	insert(".wml", "text/vnd.wap.wml");
	insert(".wmlc", "application/vnd.wap.wmlc");
	insert(".wmls", "text/vnd.wap.wmlscript");
	insert(".wmlsc", "application/vnd.wap.wmlscriptc");
	insert(".word", "application/msword");
	insert(".wp", "application/wordperfect");
	insert(".wp5", "application/wordperfect6.0");
	insert(".wp6", "application/wordperfect");
	insert(".wpd", "application/wordperfect");
	insert(".wri", "application/mswrite");
	insert(".wrl", "model/vrml");
	insert(".wrz", "model/vrml");
	insert(".wsc", "text/scriplet");
	insert(".x-png", "image/png");
	insert(".xbm", "image/xbm");
	insert(".xgz", "xgl/drawing");
	insert(".xif", "image/vnd.xiff");
	insert(".xl", "application/excel");
	insert(".xla", "application/excel");
	insert(".xlb", "application/vnd.ms-excel");
	insert(".xlc", "application/vnd.ms-excel");
	insert(".xld", "application/excel");
	insert(".xlk", "application/excel");
	insert(".xll", "application/vnd.ms-excel");
	insert(".xlm", "application/vnd.ms-excel");
	insert(".xls", "application/vnd.ms-excel");
	insert(".xlt", "application/excel");
	insert(".xlv", "application/excel");
	insert(".xlw", "application/vnd.ms-excel");
	insert(".xm", "audio/xm");
	insert(".xml", "text/xml");
	insert(".xmz", "xgl/movie");
	insert(".xpm", "image/xpm");
	insert(".zip", "application/zip");
	insert(".zoo", "application/octet-stream");
}

const QByteArray MimeTypeMapper::operator[](QByteArray key) const
{
	if (contains(key)) return value(key);
	else return "application/octet-stream";

}
