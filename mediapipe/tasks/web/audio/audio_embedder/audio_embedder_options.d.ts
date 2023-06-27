/**
 * Copyright 2022 The MediaPipe Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import {EmbedderOptions} from '../../../../tasks/web/core/embedder_options';
import {TaskRunnerOptions} from '../../../../tasks/web/core/task_runner_options';

/** Options to configure the MediaPipe Audio Embedder Task */
export declare interface AudioEmbedderOptions extends EmbedderOptions,
                                                      TaskRunnerOptions {}
