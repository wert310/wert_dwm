#!/usr/bin/env bash
set -o errexit -o noclobber -o nounset -o pipefail

HUE=(-level 0%,100%,0.6)
EFFECT=(-filter Gaussian -resize 20% -define filter:sigma=1.5 -resize 500.5%)
# greyscale HUE=(-level 0%,100%,0.6 -set colorspace Gray -separate -average)
# pixelate EFFECT=(-scale 10% -scale 1000%)
IMAGE="$(mktemp).png"
trap 'rm -f "$IMAGE"' EXIT
scrot -z "$IMAGE"
convert "$IMAGE" "${HUE[@]}" "${EFFECT[@]}" "$IMAGE"
i3lock -n -i "$IMAGE"
