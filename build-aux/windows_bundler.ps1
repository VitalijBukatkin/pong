
if (!(Test-Path -Path builddir)) {
    Write-Host "Setup project ..." -f Yellow
    meson setup builddir
}

Write-Host "Compile executables ..." -f Yellow
meson compile -C builddir

Write-Host "Creating distribution ..." -f Yellow
New-Item -ItemType "directory" -Path "builddir/pong/bin" -Force | Out-Null
Copy-Item "builddir/subprojects/SDL2-2.28.5/sdl2.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/freetype-2.13.2/freetype-6.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/SDL2_image-2.6.3/sdl2image.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/libvorbis-1.3.7/lib/vorbis-0.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/SDL2_ttf-2.20.1/sdl2_ttf.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/libvorbis-1.3.7/lib/vorbisfile-3.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/libvorbis-1.3.7/lib/vorbisenc-2.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/SDL2_mixer-2.6.2/sdl2mixer.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/libogg-1.3.5/src/ogg.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/subprojects/libpng-1.6.40/png16-16.dll" -Destination "builddir/pong/bin" -Force
Copy-Item "builddir/pong.exe" -Destination "builddir/pong/bin" -Force
Copy-Item "themes" -Destination "builddir/pong" -Recurse -Force

Compress-Archive -Path "builddir/pong" -DestinationPath "builddir/pong.zip" -Update

Write-Host "Created distribution archive builddir/pong.zip" -f Green
