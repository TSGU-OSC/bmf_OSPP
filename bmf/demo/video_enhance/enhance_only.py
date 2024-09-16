#!/usr/bin/env python
# -*- coding: utf-8 -*-

input_file = "inputs/example_960_540.mp4"
output_file = "output.mp4"
output_compose_file = "output_compose.mp4"

import bmf


def run():
    graph = bmf.graph()
    video = graph.decode({
        "input_path": input_file,
        # "loglevel": "debug",
        },
    )

    enhance = bmf.module(
        [video["video"]],
        "EnhanceModule",
        option={
            "fp32": True,
            "output_scale": 2,
            "thread": 3,
        },
        entry="enhance_module.EnhanceModule",
        input_manager="immediate",
    )

    bmf.encode(
        enhance[0],
        video["audio"],
        {
            "video_params": {
                "g": "50",
                "preset": "veryfast",
                "bf": 0,
                "vsync": "vfr",
                "max_fr": 30,
            },
            "audio_params": {
                "sample_rate": 44100,
                "codec": "aac"
            },
            # "loglevel": "debug",
            "output_path": output_file,
        },
    )
    graph.set_option({"dump_graph": 1})
    graph.run()


if __name__ == "__main__":
    run()
