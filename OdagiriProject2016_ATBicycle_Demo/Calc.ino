double SPEED(double convert) {
  if(convert == 0) return -1;
  return (1000 / ((convert * 1000000 / 3600) / tire_size));
}

double RPM(double convert) {
  return (60 / convert * 1000);
}
